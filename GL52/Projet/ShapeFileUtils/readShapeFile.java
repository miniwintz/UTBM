


	private void readTraceShapeFile(File shapeFile, File dbaseFile) throws IOException {

		DBaseFileReader dbaseFileReader = new DBaseFileReader(dbaseFile);
		GISShapeFileReader reader = new GISShapeFileReader(shapeFile, MapPoint.class, dbaseFileReader);

		for (MapElement elt : reader) {
			
			MapPoint point = (MapPoint) elt;

			double X = point.getPoint().getX();
			double Y = point.getPoint().getY();
				
			Point2d lambertPosition;
			
			if(traceProjection == Projection.WGS84) {
				
				GeodesicPosition geodesicPosition = new GeodesicPosition(X, Y);
				lambertPosition = GISCoordinates.WSG84_EL2(geodesicPosition.lambda, geodesicPosition.phi);
				
			} else {
				
				lambertPosition = new Point2d(X, Y);

			}
			
			//System.out.println("\nX = " + X + ", Y = " + Y + "\n"); // FIXME DEBUG MOD
		// afficher point sur l'appli	
			try {
				Thread.sleep(period);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
				
		}
	}
