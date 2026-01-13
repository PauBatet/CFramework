# 🚀 CFramework

**CFramework** és un framework web d'alt rendiment escrit en **C**, inspirat en l'arquitectura **MTV (Model–Template–View)** de Django.  
Està dissenyat per a desenvolupadors que busquen **màxima velocitat d'execució** i una **gestió eficient de la concurrència**, mitjançant *multi-threading* i generació automàtica de codi **CRUD**.

---

## ⚡ Inici Ràpid

### 📦 Instal·lació

Descarrega l'executable `CFramework` i afegeix-lo al teu `PATH`.  
En sistemes **Linux / macOS**:

```bash
# Donar permisos d'execució
chmod +x CFramework

# Moure al directori binari de l'usuari
sudo mv CFramework /usr/local/bin/
```

---

### 🛠️ Crear un projecte nou

Inicialitza la teva primera aplicació en pocs segons:

```bash
# Crea la teva carpeta de treball
mkdir myapp && cd myapp

# Genera l'estructura inicial del projecte
CFramework

# Genera els models i sincronitza la base de dades
make migrate

# Compila i aixeca el servidor (localhost:8080 per defecte)
make run
```

---

### 📚 Documentació en local

El framework inclou un projecte de documentació que corre sobre el propi **CFramework**. Pots generar-lo per consultar-lo offline:

```bash
CFramework docu_template
cd docu_template
make migrate
make run
```

---

## 📂 Estructura del Repositori

El repositori conté tant el motor del framework com les eines de test i plantilles:

```text
.engine/                         # Nucli del framework
template/                        # Fitxers base per inicialitzar projectes
template_with_documentation/     # Web de documentació oficial
template_with_test/              # Plantilla amb tests unitaris
performance_CFramework_test/     # Benchmarks de CFramework
performance_django_test/         # Benchmarks comparatius
tests/                           # Suite de tests del nucli
```

Fitxers principals de l'aplicació:

```text
config.c     # Configuració de l'aplicació
models.c     # Definició de models
routes.c     # Definició de rutes
views.c      # Lògica de control
Makefile     # Compilació i execució
CFramework   # CLI del framework
payload.h    # Recursos incrustats
```

---

## 🛠️ Característiques Principals

- **Arquitectura MVC** – Separació clara entre dades, lògica i presentació
- **Metaprogramació** – Generació automàtica de codi CRUD
- **Multi-threading** – Pool de threads configurable
- **Persistència flexible** – SQLite i PostgreSQL
- **Robustesa** – Reinici automàtic del servidor en cas de fallada

---

## 📄 Llicència

Aquest projecte està sota la llicència **MIT**.  
Consulta el fitxer `LICENSE` per a més detalls.
