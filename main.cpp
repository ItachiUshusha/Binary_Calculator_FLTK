#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <string>
#include <algorithm>
#include <cstdio>
#include "calc.h"
#include<cmath>
#include <climits>
using namespace std;

static Fl_Light_Button *A[64];
static Fl_Light_Button *B[64];
static Fl_Light_Button *C[64];
static Fl_Button *but;
static Fl_Button *but2;
static Fl_Button *options[12];
string symb[12] = {"+", "-", "*", "/", "%", "<", ">", "~A", "~B", "&", "|", "^"};

static Fl_Double_Window* o;

int count1 = 0;
static char buff[1000];
int R = 64;
int sys = 10;
string res;
unsigned long long int c = 0;
unsigned long long int a = 0;
unsigned long long int b = 0;
int index = 0;

Fl_Input *AI=(Fl_Input *)0;
Fl_Input *BI=(Fl_Input *)0;
Fl_Input *CI=(Fl_Input *)0;

void getA()
{
    if (sys == 10) sscanf(AI->value(),"%llu", &a);
    else if (sys == 16) sscanf(AI->value(),"%llx", &a);
    else sscanf(AI->value(),"%llo", &a);
}

void getB()
{
    if (sys == 10) sscanf(BI->value(),"%llu", &b);
    else if (sys == 16) sscanf(BI->value(),"%llx", &b);
    else sscanf(BI->value(),"%llo", &b);
}

void setC()
{
    if (sys == 10) sprintf(buff,"%llu", c);
    else if (sys == 16) sprintf(buff,"%llx", c);
    else sprintf(buff,"%llo", c);
    if (c < pow(2,R) and  R!=64)
    {
        CI->value(buff);
        string c_str = inTwo(c);
        for(int i = 0; i < R; i++)
        {
            C[i]->value(0);
        }
        for (int i = 0; i < c_str.length(); i++)
        {
            if (c_str[i] == '0') {
                C[R-i-1]->value(0);
            }
            else if(c_str[i] == '1') {
                C[R-i-1]->value(1);
            }
        }
    }
    else if( R == 64 and c < ULLONG_MAX )
    {
        CI->value(buff);
        string c_str = inTwo(c);
        for(int i = 0; i < R; i++)
        {
            C[i]->value(0);
        }
        for (int i = 0; i < c_str.length(); i++)
        {
            if (c_str[i] == '0') {
                C[R-i-1]->value(0);
            }
            else if(c_str[i] == '1') {
                C[R-i-1]->value(1);
            }
        }
    }
    else CI->value("NULL");
}

void operation(Fl_Widget *widget, void*) {
    getA();
    getB();
    for (int i = 0; i < 12; i++) {
        if (widget == options[i]) {
            index = i;
        }
    }
    unsigned int mask = (1 << R) - 1;
    switch(index) {
        case 0: c = a + b; setC(); break;
        case 1: c = a - b; setC(); break;
        case 2: c = a * b; setC(); break;
        case 3: if (b != 0) {c = a / b; setC();} else CI->value("NULL"); break;
        case 4: if (b != 0) {c = a % b; setC();} else CI->value("NULL"); break;
        case 5: if (b < 64) {c = a << b; setC();} else CI->value("0"); break;
        case 6: if (b < 64) {c = a >> b; setC();} else CI->value("0"); break;
        case 7: if (R <= 16) c = (~a) & mask; else if (R == 32){ mask = (1 << 32) - 1; c = (~a) & mask;} else c = (~a); setC(); break;
        case 8: if (R <= 16) c = (~b) & mask; else if (R == 32){ mask = (1 << 32) - 1; c = (~b) & mask;} else c = (~b); setC(); break;
        case 9: c = a & b; setC(); break;
        case 10: c = a | b; setC(); break;
        case 11: c = a ^ b; setC(); break;
    }
}

static void cb_A(Fl_Light_Button*, void*)
{
    unsigned long long int vA = 0;
    for(int i = 0; i < R; i++)
    {
        if (vA < ULLONG_MAX) vA+=A[R-i-1]->value()*(1ULL<<i);
    }
    if (pow(2, R) > vA and R!=64)
    {
        if (sys == 10) sprintf(buff,"%llu", vA);
        if (sys == 16) sprintf(buff, "%llx", vA);
        if (sys == 8) sprintf(buff, "%llo", vA);
        AI->value(buff);
    }
    else if (R == 64 and vA < ULLONG_MAX )
    {
        if (sys == 10) sprintf(buff,"%llu", vA);
        if (sys == 16) sprintf(buff, "%llx", vA);
        if (sys == 8) sprintf(buff, "%llo", vA);
        AI->value(buff);
    }
    else AI->value("NULL");
}

static void cb_AI(Fl_Input*, void*)
{
    try{
        unsigned long long int num = 0;
        if (sys == 10) sscanf(AI->value(),"%llu", &num);
        else if (sys == 16) sscanf(AI->value(), "%llx", &num);
        else if (sys == 8) sscanf(AI->value(), "%llo", &num);
        res = inTwo(num);
        for(int i = 0; i < R; i++)
        {
            A[i]->value(0);
        }
        if (num < pow(2,R) and R != 64)
        {
            for (int i = 0; i < res.length(); i++)
            {
                if (res[i] == '0') {
                    A[R-i-1]->value(0);
                }
                else if(res[i] == '1') {
                    A[R - i - 1]->value(1);
                }
            }
        }
        else if ( R == 64 and num < ULLONG_MAX )
        {for (int i = 0; i < res.length(); i++)
            {
                if (res[i] == '0') {
                    A[R-i-1]->value(0);
                }
                else if(res[i] == '1') {
                    A[R - i - 1]->value(1);
                }
            }
        }
        else AI->value("NULL");
    }
    catch(...)
    {
        AI->value("NULL");
    }

    fflush(stdout);
}

static void cb_B(Fl_Light_Button*, void*)
{
    unsigned long long int vB = 0;
    for(int i = 0; i < R; i++)
    {
        vB+=B[R-i-1]->value()*(1ULL<<i);
    }
    if (sys == 10) sprintf(buff,"%llu", vB);
    if (sys == 16) sprintf(buff, "%llx", vB);
    if (sys == 8) sprintf(buff, "%llo", vB);
    if (vB < pow(2,R) and R != 64) BI->value(buff);
    else if (R == 64 and vB < ULLONG_MAX ) BI->value(buff);
    else BI->value("NULL");
}

static void cb_BI(Fl_Input*, void*)
{
    unsigned long long int num = 0;
    if (sys == 10)sscanf(BI->value(),"%llu", &num);
    else if (sys == 16) sscanf(BI->value(), "%llx", &num);
    else if (sys == 8) sscanf(BI->value(), "%llo", &num);
    res = inTwo(num);
    for(int i = 0; i < R; i++)
    {
        B[i]->value(0);
    }
    if (num < pow(2,R) and R != 64)
    {
        for (int i = 0; i < res.length(); i++)
        {
            if (res[i] == '0') {
                B[R-i-1]->value(0);
            }
            else if(res[i] == '1') {
                B[R - i - 1]->value(1);
            }
        }
    }
    else if (R==64 and num < ULLONG_MAX )
    {
        for (int i = 0; i < res.length(); i++)
        {
            if (res[i] == '0') {
                B[R-i-1]->value(0);
            }
            else if(res[i] == '1') {
                B[R - i - 1]->value(1);
            }
        }
    }
    else BI->value("NULL");
    fflush(stdout);
}

void changeSize(Fl_Widget*, void*)
{
    count1 = 0;
    delete AI;
    delete BI;
    delete CI;
    for (int i = 0 ; i < R; i++)
    {
        delete A[i];
        delete B[i];
        delete C[i];
    }
    if (R==64)
    {
        R=8;
        but->label("Разрядность:8");
        AI = new Fl_Input(180, 60, 170, 20);
        BI = new Fl_Input(180, 100, 170, 20);
        CI = new Fl_Input(180, 140, 170, 20);
        count1 = 0;
        if (sys == 8)
        {
            for (int i = R-1; i >= 0; i--)
            {
                count1++;
                if (count1<=3)
                {
                    B[i]->color(FL_GREEN);
                    A[i]->color(FL_GREEN);
                    C[i]->color(FL_GREEN);
                }
                if (count1 == 6) count1 = 0;
            }
            o->redraw();
        }
        o->resize(100, 100, 600, 400);
    }
    else if (R == 8)
    {
        count1 = 0;
        R = 16;
        but->label("Разрядность:16");
        AI = new Fl_Input(300, 60, 170, 20);
        BI = new Fl_Input(300, 100, 170, 20);
        CI = new Fl_Input(300, 140, 170, 20);
        o->resize(100, 100, 700, 400);
    }
    else if (R == 16)
    {
        count1 = 0;
        R = 32;
        but->label("Разрядность:32");
        AI = new Fl_Input(540, 60, 170, 20);
        BI = new Fl_Input(540, 100, 170, 20);
        CI = new Fl_Input(540, 140, 170, 20);
        o->resize(100, 100, 800, 400);
    }
    else if (R == 32)
    {
        count1 = 0;
        R = 64;
        but->label("Разрядность:64");
        AI = new Fl_Input(1020, 60, 170, 20);
        BI = new Fl_Input(1020, 100, 170, 20);
        CI = new Fl_Input(1020, 140, 170, 20);
        o->resize(100, 100, 1200, 400);
    }
    for (int i = 0 ; i < R; i++)
    {
        A[i] = new Fl_Light_Button(45 + i*15,60,15,20);
        A[i]->selection_color(FL_DARK_CYAN);
        B[i] = new Fl_Light_Button(45 + i*15,100,15,20);
        B[i]->selection_color(FL_DARK_CYAN);
        C[i] = new Fl_Light_Button(45 + i*15,140,15,20);
        C[i]->selection_color(FL_DARK_CYAN);
        o->add(A[i]);
        o->add(B[i]);
        o->add(C[i]);

        A[i]->callback((Fl_Callback*)cb_A);
        B[i]->callback((Fl_Callback*)cb_B);
    }
    count1 = 0;
    if (sys == 8) {
        for (int i = R - 1; i >= 0; i--) {
            count1++;
            if (count1 <= 3) {
                A[i]->color(FL_GREEN);
                B[i]->color(FL_GREEN);
                C[i]->color(FL_GREEN);
            }
            if (count1 == 6) count1 = 0;
        }
    }
    AI->callback((Fl_Callback*)cb_AI);
    AI->when(FL_WHEN_CHANGED);
    BI->callback((Fl_Callback*)cb_BI);
    BI->when(FL_WHEN_CHANGED);
    BI->color(FL_WHITE);
    o->add(AI);
    o->add(BI);
    o->add(CI);

    o->redraw();
}

void changeSys(Fl_Widget*, void*)
{
    unsigned long long int vA = 0;
    unsigned long long int vB = 0;
    unsigned long long int vC = 0;
    for(int i = 0; i < R; i++)
    {
        vA+=A[R-i-1]->value()*(1ULL<<i);
        vB+=B[R-i-1]->value()*(1ULL<<i);
        vC+=C[R-i-1]->value()*(1ULL<<i);
    }
    AI->value(NULL);
    BI->value(NULL);
    CI->value(NULL);
    if(sys == 10)
    {
        sys = 16;
        AI->value(inSixteen(vA).c_str());
        BI->value(inSixteen(vB).c_str());
        CI->value(inSixteen(vC).c_str());
        but2->label("16");
    }
    else if(sys==16)
    {
        sys = 8;
        AI->value(inEight(vA).c_str());
        BI->value(inEight(vB).c_str());
        CI->value(inEight(vC).c_str());
        count1 = 0;
        for (int i = R-1; i >= 0; i--)
        {
            count1++;
            if (count1<=3)
            {
                A[i]->color(FL_GREEN);
                B[i]->color(FL_GREEN);
                C[i]->color(FL_GREEN);
            }
            if (count1 == 6) count1 = 0;
        }
        o->redraw();
        but2->label("8");
    }
    else if(sys == 8)
    {
        sys = 10;
        sprintf(buff, "%llu", vA);
        AI->value(buff);
        sprintf(buff, "%llu", vB);
        BI->value(buff);
        sprintf(buff, "%llu", vC);
        CI->value(buff);
        but2->label("10");
        for (int i = 0; i < R; i++)
        {
            A[i]->color(FL_WHITE);
            B[i]->color(FL_WHITE);
            C[i]->color(FL_WHITE);
        }
        o->redraw();
    }
    fflush(stdout);
}


int main(int argc, char **argv) {
    Fl_Double_Window* w;
    {
        o = new Fl_Double_Window(1200, 380);
        w = o;
        if (w) {/* empty */}
        for (int i = 0; i < R; i++) {
            A[i] = new Fl_Light_Button(45 + i * 15, 60, 15, 20);
            A[i]->selection_color(FL_DARK_CYAN);
            B[i] = new Fl_Light_Button(45 + i * 15, 100, 15, 20);
            B[i]->selection_color(FL_DARK_CYAN);
            C[i] = new Fl_Light_Button(45 + i * 15, 140, 15, 20);
            C[i]->selection_color(FL_DARK_CYAN);

            A[i]->callback((Fl_Callback *) cb_A);
            B[i]->callback((Fl_Callback *) cb_B);

        }

        for (int i = 0; i < 12; i++) {
            options[i] = new Fl_Button(105 + 40 * i, 285, 35, 20, symb[i].c_str());
            options[i]->callback(operation);

        }
        {
            AI = new Fl_Input(1020, 60, 170, 20);
            AI->callback((Fl_Callback*)cb_AI);
            AI->when(FL_WHEN_CHANGED);
        }
        {
            BI = new Fl_Input(1020, 100, 170, 20);
            BI->callback((Fl_Callback*)cb_BI);
            BI->when(FL_WHEN_CHANGED);
        }
        {
            but = new Fl_Button(105, 320, 120, 20, "Разрядность:64");
            but->callback(changeSize);
        }
        {
            but2 = new Fl_Button(240, 320, 20, 20, "10");
            but2->callback(changeSys);
        }
        {
            CI = new Fl_Input(1020, 140, 170, 20);
        }
        o->end();
    }
    o->show(argc, argv);
    return Fl::run();
}