package test;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CTabFolder;
import org.eclipse.swt.custom.CTabItem;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class MainWindow
{

    protected Shell shell;

    /**
     * Launch the application.
     * @param args
     */
    public static void main(String[] args)
    {
        try
        {
            MainWindow window = new MainWindow();
            window.open();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Open the window.
     */
    public void open()
    {
        Display display = Display.getDefault();
        createContents();
        shell.open();
        shell.layout();
        while (!shell.isDisposed())
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
        shell = new Shell();
        shell.setSize(982, 511);
        shell.setText("SWT Application");
        
        CTabFolder tabFolder = new CTabFolder(shell, SWT.BORDER);
        tabFolder.setBounds(0, 0, 980, 484);
        tabFolder.setSelectionBackground(Display.getCurrent().getSystemColor(SWT.COLOR_TITLE_INACTIVE_BACKGROUND_GRADIENT));
        
        CTabItem tabItem = new CTabItem(tabFolder, SWT.NONE);
        tabItem.setText("New Item");
        
        Canvas canvas = new Canvas(tabFolder, SWT.NONE);
        tabItem.setControl(canvas);
        
        Canvas canvas_1 = new Canvas(canvas, SWT.NONE);
        canvas_1.setBounds(793, 0, 181, 457);
        
        Button btnHaut = new Button(canvas_1, SWT.NONE);
        btnHaut.addSelectionListener(new SelectionAdapter() {
            @Override
            public void widgetSelected(SelectionEvent e) 
            {
            }
        });
        btnHaut.setBounds(48, 22, 77, 31);
        btnHaut.setText("haut");
        
        Button btnBas = new Button(canvas_1, SWT.NONE);
        btnBas.setBounds(48, 96, 77, 31);
        btnBas.setText("bas");
        
        Button btnGauche = new Button(canvas_1, SWT.NONE);
        btnGauche.setBounds(11, 59, 77, 31);
        btnGauche.setText("gauche");
        
        Button btnDroite = new Button(canvas_1, SWT.NONE);
        btnDroite.setBounds(94, 59, 77, 31);
        btnDroite.setText("droite");
        
        Button button = new Button(canvas_1, SWT.NONE);
        button.setBounds(48, 148, 77, 31);
        button.setText("+");
        
        Button button_1 = new Button(canvas_1, SWT.NONE);
        button_1.setBounds(48, 185, 77, 31);
        button_1.setText("-");
        
        Canvas canvas_2 = new Canvas(canvas, SWT.NONE);
        canvas_2.setBounds(0, 0, 787, 457);
        
        CTabItem tabItem_1 = new CTabItem(tabFolder, SWT.NONE);
        tabItem_1.setText("New Item");
        
        Canvas canvas_3 = new Canvas(tabFolder, SWT.NONE);
        tabItem_1.setControl(canvas_3);
        
        Canvas canvas_4 = new Canvas(canvas_3, SWT.NONE);
        canvas_4.setBounds(0, 0, 974, 457);
        
        Button btnAfficherTrace = new Button(canvas_4, SWT.CHECK);
        btnAfficherTrace.setBounds(27, 23, 98, 22);
        btnAfficherTrace.setText("Afficher trace");

    }
}
