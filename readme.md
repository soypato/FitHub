# FitHub: Sistema de Gestión de Gimnasios

![alt text](<FitHub logo.png>)

**Documentación, problemáticas y realización**

por Patricio Tubio ([@soypato](https://github.com/soypato)), Ignacio Acuña ([@imonety](https://github.com/imonety)), Enzo Guerci ([@ruzitosan](https://github.com/ruzito-san)), y Juan Manuel Ciardi ([@JuaniiC07](https://github.com/JuaniiC07)).

## ¿Qué hace nuestro programa?

### Gestión de Clientes

- **Alta de Clientes**: Registro y asignación de planes personalizados.
- **Modificación de Datos**: Actualizaciones fáciles de la información del cliente.
- **Baja y Restauración de Clientes**: Gestión flexible de clientes activos e inactivos.
- **Cambio de Plan**: Interfaz sencilla para modificaciones rápidas.
- **Visualización Integral**: Información detallada del progreso de cada cliente.
- **Seguridad y Privacidad**: Protección mediante inicio de sesión y contraseñas exclusivas.

### Gestión de Empleados

- **Ingreso de Empleados**: Registro de información básica y asignación de categorías.
- **Visualización de Empleados**: Diversas vistas ordenadas por legajo, DNI o edad.
- **Modificación de Datos**: Interfaz intuitiva para mantener datos actualizados.
- **Despido y Recontratación**: Flexibilidad en la gestión de empleados activos e inactivos.
- **Ordenación Personalizada**: Facilita decisiones en recursos humanos.
- **Seguridad y Privacidad**: Protección de datos mediante autenticación segura.

### Gestión de Pagos

- **Generación de Facturas**: Facturación rápida y sencilla con identificadores únicos.
- **Visualización de Facturas**: Acceso fácil a registros completos.
- **Filtrado por Monto y DNI**: Optimización de búsqueda.
- **Facturas Dadas de Baja**: Manejo eficaz de facturas inactivas.
- **Quitar y Reactivar Facturas**: Control flexible sobre facturación.
- **Seguridad y Registro**: Privacidad garantizada mediante sistemas seguros.

### Gestión de Inventario

- **Cargar Objeto**: Registro sencillo de objetos nuevos.
- **Mostrar Inventario**: Visualización clara y ordenada del inventario.
- **Desapilar Último Objeto**: Corrección rápida de errores.
- **Buscar Objeto**: Localización ágil de objetos específicos.
- **Modificar Objeto**: Actualizaciones precisas del inventario.
- **Mostrar Stock Total**: Información completa sobre el inventario acumulado.

---
# Cómo ejecutarlo
Podemos descargar la versión más estable desde el respoitorio de GitHub:

[📎 Ir a la versión más estable](https://github.com/soypato/FitHub/releases/tag/stable)

# Cómo compilarlo
- Ejecutamos en un IDE que sea compatible con el compilador de GNU GCC el main.c. Por ejemplo, Code::Block con mingw incluído puede ser una opción.
- Luego compilamos el proyecto.
---
## Estructuras Utilizadas

### Clientes y Planes de Entrenamiento

- `stArchivo`: Almacenamiento de datos personales y planes.
- `stCeldaPlanes`: Organización de planes mediante árbol binario.
- `nodoArbol`: Gestión eficiente de clientes por DNI.
- `stCliente`: Información detallada personal de clientes.

### Gestión de Empleados

- `stEmpleado`: Detalles individuales del empleado.
- `nodoListaEmpleados`: Gestión mediante listas enlazadas.

### Gestión Financiera

- `stPago`: Registro detallado de transacciones.
- `nodoListaPagos`: Organización eficiente mediante listas enlazadas.

### Inventario

- `stObjeto`: Registro detallado de objetos.
- `nodoListaInventario`: Gestión eficiente mediante estructuras tipo pila.
- `pila`: Control de objetos en el inventario mediante pila.

---

## Problemáticas y Soluciones

- **Integración de Pagos**: Uso eficiente de librerías (`ducktime.h`) para gestión del tiempo.
- **Integración de TDAs**: Separación adecuada de funciones y estructuras.
- **ABML de Clientes**: Optimización de operaciones en archivos evitando sobreescritura.
- **Integración de Cambios de Planes**: Corrección lógica para evitar datos basura.
- **Coherencia en Integración de Nuevos Clientes**: Función especializada para transiciones seguras entre planes.
- **Sobreescritura en Archivos**: Prácticas seguras en manipulación de archivos.

---

## Herramientas Utilizadas

### Git

- Control de versiones robusto.
- Facilita la colaboración y la integración.
- Respaldo seguro y constante del código.
- Seguimiento efectivo de problemas (issues).

### Trello

- Gestión visual de tareas mediante Kanban.
- Listas principales (Por comenzar, En progreso, Finalizadas).
- Listas específicas (Diario, Ideas Generales).
- Uso eficiente de etiquetas y asignación de responsabilidades.

---

**FitHub** está diseñado para brindar una experiencia intuitiva y eficiente, optimizando la gestión integral del gimnasio y facilitando tanto a empleados como a clientes el logro de sus objetivos.

### Listas Principales

Utilizamos el modelo de Kanban para las listas muy básicas.

#### Por Comenzar:

En esta lista se incluyeron todas las tareas pendientes que aún no se habían iniciado. Esto permitió visualizar de manera clara y ordenada cuáles eran las actividades que debían abordarse próximamente.

#### En Progreso:

Las tareas que se encontraban actualmente en desarrollo fueron movidas a esta lista. Proporcionó una vista instantánea del trabajo en curso y ayudó a evitar la duplicación de esfuerzos dentro del equipo.

#### Finalizadas:

Una vez que una tarea estaba completa, se movía a esta lista. Esto no solo sirvió como un registro de los logros alcanzados, sino que también proporcionó un historial claro de las actividades completadas.

### Listas Específicas

En esta lista se detallaron las estructuras de datos específicas que se planificaban utilizar en el proyecto. Cada estructura se abordó como una tarea independiente, lo que facilitó su implementación y seguimiento.

#### Diario:

Se destinó una lista exclusiva para registrar el diario del equipo. Aquí se documentaron los avances diarios, los problemas encontrados y las soluciones propuestas. Esta lista funcionó como un registro continuo del progreso del proyecto.

### Listas de Ideas

#### Ideas Generales:

En esta lista se recopilaron todas las ideas generales relacionadas con el proyecto. Cada idea se convirtió posteriormente en una tarea específica que podía ser asignada y desarrollada por algún miembro del equipo.

### Uso de Etiquetas y Asignación de Tareas

●    **Etiquetas:** Se utilizaron etiquetas para categorizar las tareas según su naturaleza (implementación, corrección de errores, documentación, etc.), lo que facilitó la identificación de las áreas clave del proyecto.

●    **Asignación de Tareas:** Cada tarea se asignó a un miembro del equipo responsable. Esto permitió una distribución equitativa de las responsabilidades y una mayor visibilidad sobre quién estaba trabajando en cada aspecto del proyecto.

Trello se convirtió en una herramienta integral para gestionar tareas, comunicarse sobre el progreso y mantener al equipo organizado. Facilitó la colaboración y ayudó a mantener un enfoque claro en los objetivos del proyecto.

 
