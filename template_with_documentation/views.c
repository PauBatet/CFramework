#include "HTTPFramework.h"
#include "Database.h"
#include "GeneratedModels.h"
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void home(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "home.html", NULL, 0);
}

void docs(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "docs.html", NULL, 0);
}

void routes_view(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "routing.html", NULL, 0);
}

void views(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "views.html", NULL, 0);
}

void models(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "models.html", NULL, 0);
}

void templates(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "templates.html", NULL, 0);
}

void docker(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "docker.html", NULL, 0);
}

void core_concepts(HTTPRequest *request, Database *db) {
    (void)db;
    render_html(request, "core_concepts.html", NULL, 0);
}
