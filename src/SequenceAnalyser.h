#ifndef SEQUENCE_ANALYSER_H
#define SEQUENCE_ANALYSER_H

namespace Comrade {
    namespace IrisXT {

//using namespace IrisFoundation;

template <typename Primitive>
class SequenceAnalyser
{
protected:  Primitive tolerance;
            double trigger_fraction;

public:     SequenceAnalyser();
            void normalise_wrt(Primitive* vect1,Primitive* vect2,int num);
            void set_tolerance(Primitive tol);
            void set_trigger_fraction(double fraction);
            bool match(Primitive* vect_1,Primitive* vect_2,int num);
            ~SequenceAnalyser();
};

template <typename Primitive>
SequenceAnalyser<Primitive>::SequenceAnalyser()
{
    tolerance=0;
    trigger_fraction=0.0;
}

template <typename Primitive>
void SequenceAnalyser<Primitive>::normalise_wrt
                                 (Primitive* vect1,
                                  Primitive* vect2,
                                  int num)
{
    Primitive max=vect2[0];

    for (int i=1; i<=num-1; i++)
    {
        if (vect2[i]>max)
        {
            max=vect2[i];
        }
    }

    for (int i=0; i<=num-1; i++)
    {
        vect1[i]/=max;
    }
}

template <typename Primitive>
void SequenceAnalyser<Primitive>::set_tolerance(Primitive tol)
{
    tolerance=tol;
}

template <typename Primitive>
void SequenceAnalyser<Primitive>::set_trigger_fraction(double fraction)
{
    trigger_fraction=fraction;
}

template <typename Primitive>
bool SequenceAnalyser<Primitive>::match(Primitive* vect_1,
                                        Primitive* vect_2,
                                        int num)
{
    int trig_limit=static_cast<int>(num*trigger_fraction);
    int start=0;

    while (start<=num-1)
    {
        int cur_trig_num=0;
        bool flag=true;

        for (int i=0; i<=num-1; i++)
        {
            Primitive error=vect_1[i]-vect_2[(start+i)%num];
            error=(error<0)?(-error):error;

            if (error>tolerance)
            {
                cur_trig_num++;

                if (cur_trig_num>trig_limit)
                {
                    flag=false;
                    break;
                }
            }
        }

        if (flag==true)
        {
            return true;
        }

        start++;
    }

    return false;
}

template <typename Primitive>
SequenceAnalyser<Primitive>::~SequenceAnalyser()
{}

}
}

#endif


