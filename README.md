# **HydroMiner**

## **Integrantes**
- Tulio Barría Águila  
- Antonia Cortes  
- Juan Carreño  

---

## **Objetivos**

### **Objetivo General**

Ejemplificar cómo un sistema basado en sensores y tecnología IoT puede ayudar a detectar y prevenir problemas de contaminación del agua en pequeñas zonas mineras. Esto se logra mediante la medición de parámetros como el TDS, el pH y la temperatura, permitiendo identificar, por ejemplo, una descarga de residuos tóxicos que alteren el equilibrio químico del agua.

### **Objetivos Específicos**

1. Medir y registrar parámetros críticos del agua: TDS, pH y temperatura.  
2. Configurar alertas automáticas para valores fuera de los rangos seguros.  
3. Implementar una interfaz web para la visualización de datos históricos y gráficos en tiempo real.  

---

## **Fases Iniciales**

1. **Pruebas de sensores y hardware**  
   - Verificar el funcionamiento de los sensores: TDS, pH y temperatura (DS18B20).  
   - Asegurar que los sensores estén correctamente conectados al Arduino Mega 2560.  
   - Confirmar la comunicación entre el microcontrolador y los sensores.  

2. **Configuración de la base de datos**  
   - Establecer una conexión con Firebase para almacenar los datos recolectados.  
   - Configurar el flujo de datos en Node-RED desde el Arduino hacia Firebase.  
   - Validar el envío de datos en tiempo real.  

3. **Desarrollo de visualización inicial**  
   - Implementar gráficos básicos utilizando **Qt Charts** para visualizar los datos en tiempo real.  
   - Crear un dashboard básico para mostrar los valores medidos por los sensores.  

4. **Definición de umbrales y alertas**  
   - Identificar rangos aceptables para los parámetros de calidad del agua (pH, TDS).  
   - Configurar alertas automáticas en Firebase para notificar excedencias de umbrales.  

5. **Validación del sistema**  
   - Realizar pruebas de funcionalidad en un entorno controlado.  
   - Detectar y corregir posibles problemas antes de la implementación final en campo.  

---

## **Aspectos Complementarios**

- **Diseño de interfaz gráfica:** Crear una visualización intuitiva y accesible para análisis rápido.  
- **Optimización del consumo:** Reducir el uso energético para facilitar la operación en zonas con acceso limitado a electricidad.  
- **Escalabilidad:** Dejar abierta la posibilidad de añadir nuevos sensores o funcionalidades en futuras iteraciones.

## Fuentes
- Parametros: https://github.com/Zerstorer037/HydroMiner/wiki/Parametros
