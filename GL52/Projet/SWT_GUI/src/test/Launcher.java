package test;
import java.io.File;
import java.io.IOException;

import fr.utbm.set.gis.io.shape.GISShapeFileReader;
import fr.utbm.set.gis.mapelement.MapPolyline;
import fr.utbm.set.io.dbase.DBaseFileReader;


public class Launcher {


	public static void main(String[] args) {
		
		
		File shapefile = new File("/home/damien/Cours/GL52/ShapeFileUtils/ShapeFiles/ROUTE_ADRESSE.SHP");
		File dbFile = new File("/home/damien/Cours/GL52/ShapeFileUtils/ShapeFiles/ROUTE_ADRESSE.DBF");
		
		DBaseFileReader dbaseFileReader;
		GISShapeFileReader reader;
		try {
			// Initialize ShapeFileReader
			dbaseFileReader = new DBaseFileReader(dbFile);
			reader = new GISShapeFileReader(shapefile, MapPolyline.class, dbaseFileReader);
		} catch (IOException e1) {
			e1.printStackTrace();
			return;
		}
		
		try {
			MainWindow window = new MainWindow(reader);
			window.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		
	}
}

