package test;

import java.util.ArrayList;

import javax.vecmath.Point2d;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CTabFolder;
import org.eclipse.swt.custom.CTabItem;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.PaintEvent;
import org.eclipse.swt.events.PaintListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Point;

import fr.utbm.set.gis.io.shape.GISShapeFileReader;
import fr.utbm.set.gis.mapelement.MapElement;
import fr.utbm.set.gis.mapelement.MapPolyline;

public class MainWindow
{

    protected Shell shlNavigator;
    protected GISShapeFileReader reader;
    
    protected ArrayList<int[]> polylines;
    
    final static double minX = 931435.0;
	final static double maxX = 961397.6;
	final static double minY = 2280558.5;
	final static double maxY = 2323666.5;
	
	
    
    
    /**
     * Editor's entry point for previewing
     * @wbp.parser.entryPoint
     */
    @SuppressWarnings("unused")
	private static void init() {
    	MainWindow window = new MainWindow(null);
		window.open();
    }

    public MainWindow(GISShapeFileReader rdr) {
    	reader = rdr;
    	
    	double scaling = Math.max((maxX - minX) / 1024, (maxY - minY) / 768);
    	polylines = new ArrayList<int[]>();
		
    	// Read ShapeFile 
		for(MapElement elt : reader) {
			// Cast current element to polyline
			MapPolyline mpl = (MapPolyline)elt;
			int pointCount = mpl.getPointCount();
			
			// myPos = {x1,y1,x2,y2,...} coordinates of polyline's points in pixels
			int[] polyline = new int[pointCount*2];
			
			// iterate over the polyline's points to generate pixel coordinates
			// to be able to draw them later (see line 157) 
			for(int i = 0; i < pointCount; i++) {
				Point2d p2d = mpl.getPointAt(i);
				
				polyline[i*2] = (int)((p2d.x - minX)/scaling);
				polyline[i*2+1] = (int)((-p2d.y + maxY)/scaling);
			}
			
			polylines.add(polyline);
		}
    }

    /**
     * Open the window.
     */
    public void open()
    {
        Display display = Display.getDefault();
        createContents();
        shlNavigator.open();
        shlNavigator.layout();
        while (!shlNavigator.isDisposed())
        {
            if (!display.readAndDispatch())
            {
                display.sleep();
            }
        }
    }

    /**
     * Create contents of the window.
     */
    protected void createContents()
    {
        shlNavigator = new Shell();
        shlNavigator.setMinimumSize(new Point(1032, 800));
        shlNavigator.setSize(982, 511);
        shlNavigator.setText("Navigator");
                
        CTabFolder tabFolder = new CTabFolder(shlNavigator, SWT.BORDER);
        tabFolder.setBounds(0, 0, 1024, 768);
        tabFolder.setSelectionBackground(Display.getCurrent().getSystemColor(SWT.COLOR_TITLE_INACTIVE_BACKGROUND_GRADIENT));
        
        CTabItem mapTab = new CTabItem(tabFolder, SWT.NONE);
        mapTab.setText("Carte");
        
        Composite mapTabComposite = new Composite(tabFolder, SWT.NONE);
        mapTab.setControl(mapTabComposite);
        
        Button btnUp = new Button(mapTabComposite, SWT.NONE);
        btnUp.setLocation(930, 5);
        btnUp.setSize(40, 40);
        btnUp.setText("▲");
        
        Button btnDown = new Button(mapTabComposite, SWT.NONE);
        btnDown.setLocation(930, 85);
        btnDown.setSize(40, 40);
        btnDown.setText("▼");
        
        Button btnLeft = new Button(mapTabComposite, SWT.NONE);
        btnLeft.setBounds(890, 45, 40, 40);
        btnLeft.setText("◀");
        
        Button btnRight = new Button(mapTabComposite, SWT.NONE);
        btnRight.setBounds(970, 45, 40, 40);
        btnRight.setText("▶");
        
        Button btnCenter = new Button(mapTabComposite, SWT.NONE);
        btnCenter.setBounds(930, 45, 40, 40);
        btnCenter.setText("O");
        
        Button btnZoomIn = new Button(mapTabComposite, SWT.NONE);
        btnZoomIn.setBounds(930, 135, 40, 40);
        btnZoomIn.setText("+");
        
        Button btnZoomOut = new Button(mapTabComposite, SWT.NONE);
        btnZoomOut.setBounds(930, 175, 40, 40);
        btnZoomOut.setText("-");
        
        Canvas mapCanvas = new Canvas(mapTabComposite, SWT.BORDER);
        mapCanvas.setSize(1017, 740);
        
        
        mapCanvas.addPaintListener(new PaintListener() {
			/**
			 * Paint inside the canvas
			 */
			@Override
			public void paintControl(PaintEvent e) {
				GC gc = e.gc;
				long time = System.currentTimeMillis();
				
				//iterate over polylines' sets of coordinates
				for(int[] polyline : polylines) {
					// draw the polyline
					gc.drawPolyline(polyline);
				}
				time = System.currentTimeMillis() - time;
				System.out.println("Took " + time + " ms");
			}
		});
        
        CTabItem settingsTab = new CTabItem(tabFolder, SWT.NONE);
        settingsTab.setText("Paramètres");
        
        Composite settingsTabComposite = new Composite(tabFolder, SWT.NONE);
        settingsTab.setControl(settingsTabComposite);
        
        Button button = new Button(settingsTabComposite, SWT.CHECK);
        button.setText("Afficher trace");
        button.setBounds(0, 0, 1018, 741);
        
    }
}
