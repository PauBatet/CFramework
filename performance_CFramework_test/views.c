#include "HTTPFramework.h"
#include "Database.h"
#include "GeneratedModels.h"
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void home(HTTPRequest *request, Database *db) {
    (void)db;
    const char *body = "Hello World";
    HTTPServer_send_response(request, body, "", 200, "");
}
