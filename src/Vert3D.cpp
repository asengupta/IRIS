#include "Vert3D.h"

Comrade::Iris3D::Coordinate::Coordinate()
{
    pt.array[0][0]=0;
    pt.array[0][1]=0;
    pt.array[0][2]=0;
    pt.array[0][3]=1;
}

Comrade::Iris3D::Coordinate::Coordinate(double x, double y, double z)
{
    pt.array[0][0]=x;
    pt.array[0][1]=y;
    pt.array[0][2]=z;
    pt.array[0][3]=1;
}

Comrade::Iris3D::Point Comrade::Iris3D::Coordinate::return_data()
{
    Point answer;
    answer.array[0][0]=pt.array[0][0];
    answer.array[0][1]=pt.array[0][1];
    answer.array[0][2]=pt.array[0][2];
    answer.array[0][3]=pt.array[0][3];

    return answer;
}

double Comrade::Iris3D::Coordinate::get_x()
{
    return pt.array[0][0];
}

double Comrade::Iris3D::Coordinate::get_y()
{
    return pt.array[0][1];
}

double Comrade::Iris3D::Coordinate::get_z()
{
    return pt.array[0][2];
}

void Comrade::Iris3D::Coordinate::input(Point para)
{
    pt=para;
}

void Comrade::Iris3D::Coordinate::input(double x, double y, double z)
{
    pt.array[0][0]=x;
    pt.array[0][1]=y;
    pt.array[0][2]=z;
    pt.array[0][3]=1;
}

void Comrade::Iris3D::Coordinate::show()
{
    pt.show();
}

Comrade::Iris3D::Point Comrade::Iris3D::Coordinate::show_arbitrary(Comrade::Iris3D::Point pt1, Comrade::Iris3D::Point pt2, int color)
{
    double A=pt2.array[0][0]-pt1.array[0][0];
    double B=pt2.array[0][1]-pt1.array[0][1];
    double C=pt2.array[0][2]-pt1.array[0][2];


			double x1=pt1.array[0][0];
			double y1=pt1.array[0][1];
			double z1=pt1.array[0][2];

			double sin1, cos1;

			double atrans1[4][4];
			//double ainvtrans1[4][4];



			if (fabs(B)<=0.001 && fabs(C)<=0.001)
			{
				atrans1[0][0]=1;
				atrans1[0][1]=0;
				atrans1[0][2]=0;
				atrans1[0][3]=0;
				atrans1[1][0]=0;
				atrans1[1][1]=cos(0);
				atrans1[1][2]=sin(0);
				atrans1[1][3]=0;
				atrans1[2][0]=0;
				atrans1[2][1]=-sin(0);
				atrans1[2][2]=cos(0);
				atrans1[2][3]=0;
				atrans1[3][0]=0;
				atrans1[3][1]=0;
				atrans1[3][2]=0;
				atrans1[3][3]=1;
			}


			else
			{
				sin1=B/sqrt(pow(B,2)+pow(C,2));
				cos1=C/sqrt(pow(B,2)+pow(C,2));

				atrans1[0][0]=1;
				atrans1[0][1]=0;
				atrans1[0][2]=0;
				atrans1[0][3]=0;
				atrans1[1][0]=0;
				atrans1[1][1]=cos1;
				atrans1[1][2]=sin1;
				atrans1[1][3]=0;
				atrans1[2][0]=0;
				atrans1[2][1]=-sin1;
				atrans1[2][2]=cos1;
				atrans1[2][3]=0;
				atrans1[3][0]=0;
				atrans1[3][1]=0;
				atrans1[3][2]=0;
				atrans1[3][3]=1;
			}

			double cos2=sqrt(pow(B,2)+pow(C,2))/sqrt(pow(A,2)+pow(B,2)+pow(C,2));
			double sin2=A/sqrt(pow(A,2)+pow(B,2)+pow(C,2));

			double atrans2[4][4]={{cos2,0,sin2,0},{0,1,0,0},
					  {-sin2,0,cos2,0},{0,0,0,1}};

			double atranslate[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},
					     {-x1,-y1,-z1,1}};

			double ascaletrans[4][4]={{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,0,0,1}};


			Matrix4x4 trans1;
			trans1.input(atrans1);
			//trans1.show();

			Matrix4x4 trans2;
			trans2.input(atrans2);
			//trans2.show();

			Matrix4x4 translate;
			translate.input(atranslate);
			//translate.show();


			Matrix4x4 scaletrans;
			scaletrans.input(ascaletrans);

			Point answer;
      answer.input(0,0,0,0);
			answer=pt;

			answer=multiply(answer,translate);
			answer=multiply(answer,trans1);
			answer=multiply(answer,trans2);
			answer=multiply(answer,scaletrans);

			draw(answer,color);

			return answer;

		}

		void Comrade::Iris3D::Coordinate::translate(int tx, int ty, int tz)
		{
			double arr[4][4]={{1,0,0,0}, {0,1,0,0}, {0,0,1,0},
							 {tx,ty,tz,1}};

			mat.input(arr);
			Point answer=multiply(pt, mat);
			pt=answer;
		}

		void Comrade::Iris3D::Coordinate::scale(double sx, double sy, double sz)
		{
			double arr[4][4]={{sx,0,0,0}, {0,sy,0,0}, {0,0,sz,0},
							 {0,0,0,1}};
			mat.input(arr);
			Point answer=multiply(pt, mat);
			pt=answer;
		}

		void Comrade::Iris3D::Coordinate::rotate_about_z(double theta)
		{
			double rad=deg_to_rad(theta);
			double arr[4][4]={{cos(rad),sin(rad),0,0},
							 {-sin(rad),cos(rad),0,0},
							 {0,0,1,0},{0,0,0,1}};
			mat.input(arr);
			Point answer=multiply(pt,mat);
			pt=answer;
		}

		void Comrade::Iris3D::Coordinate::rotate_about_x(double theta)
		{
			double rad=deg_to_rad(theta);
			double arr[4][4]={{1,0,0,0},{0,cos(rad), sin(rad),0},
							 {0,-sin(rad),cos(rad),0},{0,0,0,1}};
			mat.input(arr);
			Point answer=multiply(pt,mat);
			pt=answer;
		}

		void Comrade::Iris3D::Coordinate::rotate_about_y(double theta)
		{
			double rad=deg_to_rad(theta);
			double arr[4][4]={{cos(rad),0,-sin(rad),0},
							 {0,1,0,0},
							 {sin(rad),0,cos(rad),0},
							 {0,0,0,1}};
			mat.input(arr);
			Point answer=multiply(pt,mat);
			pt=answer;
		}

		void Comrade::Iris3D::Coordinate::rotate_about_parametric(Comrade::Iris3D::Parametric line, double theta)
		{

			double A=line.A;
			double B=line.B;
			double C=line.C;

			double x1=line.x1;
			double y1=line.y1;
			double z1=line.z1;

			double rad=deg_to_rad(theta);

			double sin1, cos1;

			double atrans1[4][4];
			double ainvtrans1[4][4];

			if (fabs(B)<=0.001 && fabs(C)<=0.001)
			{
				atrans1[0][0]=1;               ainvtrans1[0][0]=1;
				atrans1[0][1]=0;               ainvtrans1[0][1]=0;
				atrans1[0][2]=0;               ainvtrans1[0][2]=0;
				atrans1[0][3]=0;               ainvtrans1[0][3]=0;
				atrans1[1][0]=0;               ainvtrans1[1][0]=0;
				atrans1[1][1]=cos(rad);        ainvtrans1[1][1]=cos(rad);
				atrans1[1][2]=sin(rad);        ainvtrans1[1][2]=-sin(rad);
				atrans1[1][3]=0;               ainvtrans1[1][3]=0;
				atrans1[2][0]=0;               ainvtrans1[2][0]=0;
				atrans1[2][1]=-sin(rad);       ainvtrans1[2][1]=sin(rad);
				atrans1[2][2]=cos(rad);        ainvtrans1[2][2]=cos(rad);
				atrans1[2][3]=0;               ainvtrans1[2][3]=0;
				atrans1[3][0]=0;               ainvtrans1[3][0]=0;
				atrans1[3][1]=0;               ainvtrans1[3][1]=0;
				atrans1[3][2]=0;               ainvtrans1[3][2]=0;
				atrans1[3][3]=1;               ainvtrans1[3][3]=1;
			}


			else
			{
				sin1=B/sqrt(pow(B,2)+pow(C,2));
				cos1=C/sqrt(pow(B,2)+pow(C,2));

				atrans1[0][0]=1;               ainvtrans1[0][0]=1;
				atrans1[0][1]=0;               ainvtrans1[0][1]=0;
				atrans1[0][2]=0;               ainvtrans1[0][2]=0;
				atrans1[0][3]=0;               ainvtrans1[0][3]=0;
				atrans1[1][0]=0;               ainvtrans1[1][0]=0;
				atrans1[1][1]=cos1;        ainvtrans1[1][1]=cos1;
				atrans1[1][2]=sin1;        ainvtrans1[1][2]=-sin1;
				atrans1[1][3]=0;               ainvtrans1[1][3]=0;
				atrans1[2][0]=0;               ainvtrans1[2][0]=0;
				atrans1[2][1]=-sin1;       ainvtrans1[2][1]=sin1;
				atrans1[2][2]=cos1;        ainvtrans1[2][2]=cos1;
				atrans1[2][3]=0;               ainvtrans1[2][3]=0;
				atrans1[3][0]=0;               ainvtrans1[3][0]=0;
				atrans1[3][1]=0;               ainvtrans1[3][1]=0;
				atrans1[3][2]=0;               ainvtrans1[3][2]=0;
				atrans1[3][3]=1;               ainvtrans1[3][3]=1;

				//atrans1[4][4]={{1,0,0,0},{0,cos1,sin1,0},
				//			{0,-sin1,cos1,0},{0,0,0,1}};
				// Legacy code
			}

			double cos2=sqrt(pow(B,2)+pow(C,2))/sqrt(pow(A,2)+pow(B,2)+pow(C,2));
			double sin2=A/sqrt(pow(A,2)+pow(B,2)+pow(C,2));


			double atrans2[4][4]={{cos2,0,sin2,0},{0,1,0,0},
						{-sin2,0,cos2,0},{0,0,0,1}};

			double atranslate[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},
							 {-x1,-y1,-z1,1}};

			//double ainvtrans1[4][4]={{1,0,0,0},{0,cos1,-sin1,0},
			//			{0,sin1,cos1,0},{0,0,0,1}};
			/* Legacy code - may be used in distress */

			double ainvtrans2[4][4]={{cos2,0,-sin2,0},{0,1,0,0},
						{sin2,0,cos2,0},{0,0,0,1}};
			double ainvtranslate[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},
							 {x1,y1,z1,1}};
			double arotate[4][4]={{cos(rad),sin(rad),0,0},
								{-sin(rad),cos(rad),0,0},
								{0,0,1,0},{0,0,0,1}};

			Matrix4x4 trans1;
			trans1.input(atrans1);
			//trans1.show();

			Matrix4x4 trans2;
			trans2.input(atrans2);
			//trans2.show();

			Matrix4x4 translate;
			translate.input(atranslate);
			//translate.show();


			Matrix4x4 invtrans1;
			invtrans1.input(ainvtrans1);

			Matrix4x4 invtrans2;
			invtrans2.input(ainvtrans2);

			Matrix4x4 rotate;
			rotate.input(arotate);

			Matrix4x4 invtranslate;
			invtranslate.input(ainvtranslate);
			//invtranslate.show();

			Point answer=pt;


			answer=multiply(answer,translate);

			answer=multiply(answer,trans1);

			//answer.show();
			//trans1.show();

			answer=multiply(answer,trans2);
			answer=multiply(answer,rotate);
			answer=multiply(answer,invtrans2);
			answer=multiply(answer,invtrans1);

			answer.array[0][0]+=x1;
			answer.array[0][1]+=y1;
			answer.array[0][2]+=z1;
			answer.array[0][3]=1;

			pt=answer;
		}

		void Comrade::Iris3D::Coordinate::world_to_sensor(Comrade::Iris3D::Parametric line,
                                         double x_up,
                                         double y_up,
                                         double z_up)
		{
			double A=line.A;
			double B=line.B;
			double C=line.C;

			double x1=line.x1;
			double y1=line.y1;
			double z1=line.z1;

            double rad=0;
			double sin1, cos1;

			double atrans1[4][4];

            if (fabs(B)<=0.001 && fabs(C)<=0.001)
			{
				atrans1[0][0]=1;
				atrans1[0][1]=0;
				atrans1[0][2]=0;
				atrans1[0][3]=0;
				atrans1[1][0]=0;
				atrans1[1][1]=cos(rad);
				atrans1[1][2]=sin(rad);
				atrans1[1][3]=0;
				atrans1[2][0]=0;
				atrans1[2][1]=-sin(rad);
				atrans1[2][2]=cos(rad);
				atrans1[2][3]=0;
				atrans1[3][0]=0;
				atrans1[3][1]=0;
				atrans1[3][2]=0;
				atrans1[3][3]=1;
			}


			else
			{
				sin1=B/sqrt(pow(B,2)+pow(C,2));
				cos1=C/sqrt(pow(B,2)+pow(C,2));

				atrans1[0][0]=1;
				atrans1[0][1]=0;
				atrans1[0][2]=0;
				atrans1[0][3]=0;
				atrans1[1][0]=0;
				atrans1[1][1]=cos1;
				atrans1[1][2]=sin1;
				atrans1[1][3]=0;
				atrans1[2][0]=0;
				atrans1[2][1]=-sin1;
				atrans1[2][2]=cos1;
				atrans1[2][3]=0;
				atrans1[3][0]=0;
				atrans1[3][1]=0;
				atrans1[3][2]=0;
				atrans1[3][3]=1;
			}

			double cos2=sqrt(pow(B,2)+pow(C,2))/sqrt(pow(A,2)+pow(B,2)+pow(C,2));
			double sin2=A/sqrt(pow(A,2)+pow(B,2)+pow(C,2));


			double atrans2[4][4]={{cos2,0,sin2,0},{0,1,0,0},
						          {-sin2,0,cos2,0},{0,0,0,1}};

			double atranslate[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},
							 {-x1,-y1,-z1,1}};

			Matrix4x4 trans1;
			trans1.input(atrans1);
			//trans1.show();

			Matrix4x4 trans2;
			trans2.input(atrans2);
			//trans2.show();

			Matrix4x4 translate;
			translate.input(atranslate);
			//translate.show();

			//Matrix4x4 invtranslate;
			//invtranslate.input(ainvtranslate);
			//invtranslate.show();

			Point answer=pt;

            answer=multiply(answer,translate);
            answer=multiply(answer,trans1);
			answer=multiply(answer,trans2);

            answer.array[0][0]=(fabs(answer.array[0][0])<=1e-5)?0:answer.array[0][0];
            answer.array[0][1]=(fabs(answer.array[0][1])<=1e-5)?0:answer.array[0][1];
            answer.array[0][2]=(fabs(answer.array[0][2])<=1e-5)?0:answer.array[0][2];
            answer.array[0][3]=1;

            Point dup;
            dup.array[0][0]=x_up;
            dup.array[0][1]=y_up;
            dup.array[0][2]=z_up;
            dup.array[0][3]=1;

            dup=multiply(dup,trans1);
            dup=multiply(dup,trans2);

            double xup_vp=dup.array[0][0];
            double yup_vp=dup.array[0][1];


            double rup=sqrt(xup_vp*xup_vp+
                            yup_vp*yup_vp);

            double arz[4][4];

            for (int i=0; i<=3; i++)
            {
                for (int j=0; j<=3; j++)
                {
                    arz[i][j]=0;
                }
            }

            arz[2][2]=1;
            arz[3][3]=1;
            arz[0][0]=yup_vp/rup;
            arz[0][1]=xup_vp/rup;
            arz[1][0]=-xup_vp/rup;
            arz[1][1]=yup_vp/rup;

            Matrix4x4 rz;
            rz.input(arz);

            answer=multiply(answer,rz);
            pt=answer;
		}

		Comrade::Iris3D::Point Comrade::Iris3D::Coordinate::parallel_project(Comrade::Iris3D::Parametric vector,int color)
		{
			Point answer=pt;
			double array[4][4]={{1,0,0,0},{0,1,0,0},{-vector.A/vector.C,-vector.B/vector.C,1,0},
				                {0,0,0,1}};
			Matrix4x4 arr;
			arr.input(array);

			answer=multiply(answer,arr);
			draw(answer,color);
			return answer;
		}


		void Comrade::Iris3D::Coordinate::draw(Comrade::Iris3D::Point coord, int colour)
		{
      std::cout<<coord.array[0][0];
      std::cout<<colour;
      
      //putpixel(MAP_X+coord.array[0][0],MAP_Y+coord.array[0][1],colour);
		}


/*int main()
{
	clrscr();
	Coordinate coord(0,5,0);
	coord.show();
	cout<<endl;
	parametric axis={1,0,0,0,0,0};
	coord.rotate_about_parametric(axis,180);
	coord.show();
	getch();
	return 0;
}*/



