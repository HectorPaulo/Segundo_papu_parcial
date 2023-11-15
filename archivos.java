import java.io.File;
import javax.swing.JOptionPane;

public class archivos {
    public static void main(String[] args) {
        while (true) {
            int numero = Integer.parseInt(JOptionPane.showInputDialog("Elige una opción."));
            JOptionPane.showMessageDialog(null, "La opción es: " + numero);
            switch (numero) {
                case 1: {
                    String directorio = JOptionPane.showInputDialog("Ingresa la ruta: ");
                    JOptionPane.showMessageDialog(null, "La ruta es " + directorio);
                    crearDirectorio(directorio);
                    break;
                }
                case 2: {
                    String nombreArchivo = JOptionPane.showInputDialog("Ingresa la ruta CON EL NOMBRE DEL ARCHIVO con su extensión");
                    JOptionPane.showMessageDialog(null, "La ruta del archivo es: " + nombreArchivo);
                    crearArchivo(nombreArchivo);
                    break;
                }
                case 3: {
                    JOptionPane.showMessageDialog(null, "Esta es la opción 3.");
                    break;
                }
                default: {
                    JOptionPane.showMessageDialog(null, "Elige una opción válida POR FAVOR.");
                    break;
                }
            }
        }
    }

    private static void crearDirectorio(String rutaDirectorio) {
        File directorio = new File(rutaDirectorio);
        if (directorio.exists()) {
            JOptionPane.showMessageDialog(null, "Lástima, el directorio ya existe.");
        } else {
            boolean exito = directorio.mkdirs();
            if (exito) {
                JOptionPane.showMessageDialog(null, "Directorio creado con éxito.");
            } else {
                JOptionPane.showMessageDialog(null, "Error al crear el directorio.");
            }
        }
    }

    private static void crearArchivo(String rutaArchivo) {
        File archivo = new File(rutaArchivo);
        if (archivo.exists()) {
            JOptionPane.showMessageDialog(null, "Lástima, el archivo ya existe.");
        } else {
            try {
                boolean exito = archivo.createNewFile();
                if (exito) {
                    JOptionPane.showMessageDialog(null, "Archivo creado con éxito.");
                } else {
                    JOptionPane.showMessageDialog(null, "Error al crear el archivo.");
                }
            } catch (Exception e) {
                JOptionPane.showMessageDialog(null, "Error al crear el archivo: ");
            }
        }
    }
}