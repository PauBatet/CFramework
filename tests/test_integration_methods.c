#define _DEFAULT_SOURCE
#include <unistd.h>
#include "unity/unity.h"
#include "../.engine/Database/Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define BASE_URL "http://localhost:8080"
Database *test_db;
int shared_group_id = 0;

// --- Obligatoris per Unity ---
void setUp(void) {
    db_open(&test_db);
}

void tearDown(void) {
    db_close(test_db);
}

// Funció auxiliar per executar curl i capturar la sortida
bool curl_output_contains(const char *method, const char *endpoint, const char *expected_text) {
    char command[512];
    char buffer[1024];
    bool found = false;

    // Construïm la comanda curl. -s per silent, -X per mètode
    sprintf(command, "curl -s -X %s %s%s", method, BASE_URL, endpoint);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) return false;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, expected_text) != NULL) {
            found = true;
            break;
        }
    }
    pclose(fp);
    return found;
}

// Funció auxiliar per capturar el codi HTTP
int curl_get_status(const char *url) {
    char command[512];
    char buffer[16];
    sprintf(command, "curl -s -o /dev/null -w \"%%{http_code}\" %s%s", BASE_URL, url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) return -1;

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        pclose(fp);
        return atoi(buffer);
    }
    pclose(fp);
    return -1;
}

// --- VERIFICACIÓ RF02: GESTIÓ DE MÈTODES ---
void test_RF02_HTTP_Methods(void) {
    TEST_ASSERT_TRUE_MESSAGE(
        curl_output_contains("GET", "/test-methods", "Mètode GET detectat"),
        "Error: El router no ha identificat correctament el mètode GET"
    );
    TEST_ASSERT_TRUE_MESSAGE(
        curl_output_contains("POST", "/test-methods", "Mètode POST detectat"),
        "Error: El router no ha identificat correctament el mètode POST"
    );
    TEST_ASSERT_TRUE_MESSAGE(
        curl_output_contains("PUT", "/test-methods", "Mètode PUT detectat"),
        "Error: El router no ha identificat correctament el mètode PUT"
    );
    TEST_ASSERT_TRUE_MESSAGE(
        curl_output_contains("DELETE", "/test-methods", "Mètode DELETE detectat"),
        "Error: El router no ha identificat correctament el mètode DELETE"
    );
}

// --- VERIFICACIÓ RF03: 404 NOT FOUND ---
void test_RF03_NotFound(void) {
    int status = curl_get_status("/ruta-que-no-existeix");
    TEST_ASSERT_EQUAL_INT_MESSAGE(404, status, "RF03: El servidor hauria de retornar 404 per rutes inexistents");
}

// --- VERIFICACIÓ RF05 i RF06: PARÀMETRES I RENDERITZACIÓ ---
void test_RF05_RF06_Params_And_Rendering(void) {
    // Provem d'enviar un DNI per la URL i veure si el router l'extreu (RF05) 
    // i la vista el pinta (RF06)
    const char *test_dni = "44556677Z";
    char endpoint[128];
    sprintf(endpoint, "/user/%s/profile", test_dni);
    
    TEST_ASSERT_TRUE_MESSAGE(
        curl_output_contains("GET", endpoint, test_dni),
        "RF05/RF06: No s'ha trobat el paràmetre :id renderitzat a l'HTML"
    );
}

// RF13: Una petició lenta no bloqueja les altres (Multi-threading/Non-blocking)
void test_RF13_Non_Blocking_Concurrency(void) {
    // 1. Enviem una petició a /wait que triga molt (background)
    char long_cmd[256];
    sprintf(long_cmd, "curl -s %s/wait > /dev/null &", BASE_URL);
    system(long_cmd);
    
    // Deixem un marge perquè el servidor l'accepti
    usleep(100000); 

    // 2. Intentem accedir a la home immediatament
    time_t start = time(NULL);
    int status = curl_get_status("/");
    time_t end = time(NULL);

    TEST_ASSERT_EQUAL_INT(200, status);
    // Si ha trigat menys de 2 segons, és que no s'ha esperat als 120s del /wait
    TEST_ASSERT_TRUE_MESSAGE((end - start) < 2, "El servidor s'ha bloquejat esperant la petició lenta");
}

// --- MAIN ---
int main(void) {
    UNITY_BEGIN();
    
    // Abans de córrer, assegura't que el servidor està amunt!
    RUN_TEST(test_RF02_HTTP_Methods);
    RUN_TEST(test_RF03_NotFound);
    RUN_TEST(test_RF05_RF06_Params_And_Rendering);
    RUN_TEST(test_RF13_Non_Blocking_Concurrency);
    
    return UNITY_END();
}
