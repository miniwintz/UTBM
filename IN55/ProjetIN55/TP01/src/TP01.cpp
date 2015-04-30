#include "TP01.h"


#include "Shapes/Basis.h"
#include "Shapes/MeshBuilder.h"

#include <iostream>

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;

const GLfloat g_AngleSpeed = 10.0f;


Basis* basis;
MeshBuilder* mesh;


TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));

    basis = new Basis( 10.0 );

        std::string inputfile = "../../Models/cube.obj";
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string err = tinyobj::LoadObj(shapes,materials, inputfile.c_str());

        if (!err.empty()) {
          std::cerr << err << std::endl;
          exit(1);
        }

        std::cout << "# of shapes    : " << shapes.size() << std::endl;
        std::cout << "# of materials : " << materials.size() << std::endl;


        mesh = new MeshBuilder(shapes, materials);
}


TP01::~TP01()
{
    delete basis;
}


bool
TP01::initializeObjects()
{
	// Fond gris
    glClearColor( 1.0f,1.0f,1.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );

	// Chargement des shaders
	createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

	return true;
}


void
TP01::render()
{
	// Initialisation de la caméra
	lookAt( 0, 5, 30, 0, 0, 0 );


	// Rendu des objets
	pushMatrix();
		rotate( angle1, 0, 1, 0 );
		rotate( angle2, 1, 0, 0 );

        basis->draw();
    popMatrix();



    pushMatrix();
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 1, 0, 0 );

        mesh->draw();
    popMatrix();
}


void
TP01::keyPressEvent( QKeyEvent* event )
{
	switch( event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

		case Qt::Key_Left:
			angle1 -= g_AngleSpeed;
			break;

		case Qt::Key_Right:
			angle1 += g_AngleSpeed;
			break;

		case Qt::Key_Up:
			angle2 -= g_AngleSpeed;
			break;

		case Qt::Key_Down:
			angle2 += g_AngleSpeed;
			break;

		case Qt::Key_R:
			angle1 = angle2 = 0.0f;
			break;
	}
}
