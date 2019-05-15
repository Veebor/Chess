#include <iostream>
#include "Matrix.h"
#include <cmath>
using namespace std;

int l;
int h;
int l_2;
int h_2;

// Definiamo i delta degli spostamenti dei pezzi
double delt;
double delh;


// Definiamo la tavola di partenza
string set[64] = {"R01", "K01", "B01", "Q0", "L0", "B02", "K02", "R02",
                  "P01", "P02", "P03", "P04", "P05", "P06", "P07", "P08",
                  "0", "0", "0", "0", "0", "0", "0", "0",
                  "0", "0", "0", "0", "0", "0", "0", "0",
                  "0", "0", "0", "0", "0", "0", "0", "0",
                  "0", "0", "0", "0", "0", "0", "0", "0",
                  "P11", "P12", "P13", "P14", "P15", "P16", "P17", "P18",
                  "R11", "K11", "B11", "F1", "Q1", "B12", "K12", "R12"
                  };

// Carichiamo la tavola in un oggetto Matrice
Matrix<string> M(8, 8, set);

bool moveStart(int l, int h, int l_2, int h_2)
{
  string toMoveStart = M[l][h];
  string toMove = M[l_2][h_2];
  bool isNotValid;
  if (M[l_2][h_2] == "0")
  {
    isNotValid = false;
  }
  else
  {
    isNotValid = (toMove[1] == toMoveStart[1]);
    if (!isNotValid)
    {
      cout << toMoveStart << " mangia " << toMove << endl;
    }
  }

  return isNotValid;
};
bool antiJump(int l, int h, int l_2, int h_2,int flagAntiJump)
{
  bool antiJumpbool ;
  int delx =  l_2- l;
  int dely =  h_2- h;
  int k;
  int j;

  if (flagAntiJump == 0 ){

    if (l_2 < l)
    {
      k = l_2 + 1;
    }
    else
    {
      k = l_2 - 1;
    }
    if (h_2 < h)
    {
      j = h_2 + 1;
    }
    else
    {
      j = h_2 - 1;
    }

    antiJumpbool = false;
    string toJumpStart = M[l][h];
    cout << toJumpStart[0] << M[l][h] << endl;

    if (delh == 0)
    {
      while (M[k][h] != M[l][h])
      {
        if (M[k][h] == "0")
        {

          cout << "k:" << M[k][h] << endl;
          if (l_2 < l)
          {
            cout << "k:+" << endl;
            k++;
          }
          else
          {
            k--;
            cout << "k:-" << endl;
          }
        }
        else
        {

          cout << "non saltare nessuno" << M[k][h] << endl;
          antiJumpbool = true;
          break;
        }
      }
    }
    else
    {
      while (M[k][l] != M[l][h])
      {
        if (M[k][l] == "0")
        {
          cout << "k:" << M[l][j] << endl;
          if (h_2 < h)
          {
            j++;
          }
          else
          {
            j--;
          }
          cout << "j:" << M[l][j] << endl;
        }
        else
        {

          antiJumpbool = true;
          break;
        }
      }
    }
  }else if (flagAntiJump == 1) {
    cout << "dely" << dely << "delx"<< delx << endl;
    int mover0;
    int mover1;
    //////////////////////////////////////////////////////////
    if (dely*delx > 0 )
    {

     if (dely < 0 ){
        cout << "sinistra in alto"<< endl;
        k = l_2+1;
        j = h_2+1;
        mover0 = 1;
        mover1 = 1;

     }
     else
     {
       cout << "destra in basso"<< endl;
       k = l_2-1;
       j = h_2-1;
       mover0 = -1;
       mover1 = -1;


     }
     
    }
    else
    {
       if (dely > 0 ){
        cout << "destra in alto"<< endl;
        k = l_2+1;
        j = h_2-1;
        mover0 = +1;
        mover1 = -1;

     }
     else
     {
        cout << "sinistra in basso" << endl;
        k = l_2-1;
        j = h_2+1;
        mover0 = -1;
        mover1 = +1;
     }
      
    }
  
  while (M[k][j] != M[l][h])
    {
      if (M[k][j] == "0")
      {

        cout << "k:" << M[k][j] << endl;
        k = k + mover0;
        j = j + mover1;
        
      }
      else
      {

        cout << "non saltare nessuno" << M[k][j] << endl;
        antiJumpbool = true;
        break;
      }
    }
  }
  else
  {
    cout<< "regina"<< endl;
  }
  return antiJumpbool;
};

// Definizione della classe pedone che prevede gli spostamenti di questa tipologia di pezzi
class pedone
{
public:
  int l;
  int h;
  bool validita;
  void move()
  {
    cout << "Inserire l e h " << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);

    if (delh != 0 || delt > 1)
    {
      validita = false;
    }
    else
    {
      validita = true;
    };

    if (!validita || moveStart(l, h, l_2, h_2))
    {
      cout << "Mossa non valida" << endl;
    }
    else
    {
      cout << "Mossa valida" << endl;
      if (M[l_2][h_2] == M[l][h]){
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
      }
     
    }
  }
};

class torre
{
private:
  double delt;
  double delh;

public:
  int l;
  int h;
  bool validita;

  void move()
  {
    cout << "Inserire l e h " << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    if ((delh != 0 & delt != 0) || antiJump(l, h, l_2, h_2,0) || moveStart(l, h, l_2, h_2))
    {
      cout << "Mossa non valida" << endl;
    }
    else
    {
      cout << "Mossa valida" << endl;
      if (M[l_2][h_2] == M[l][h]){
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
      }
    }
  }
};

class cavallo
{
private:
  double delt;
  double delh;

public:
  int l;
  int h;
  bool validita;

  void move()
  {
    cout << "Inserire l e h su due righe diverse" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    if ((fabs(l_2 - l) != 1 || fabs(h_2 - h) != 2) & (fabs(l_2 - l) != 2 || fabs(h_2 - h) != 1))
    {
      validita = false;
    }
    else
    { 
      if (M[l_2][h_2] == M[l][h]){
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
      }
    }
  }
};

class alfiere
{
private:
  double delt;
  double delh;

public:
  int l;
  int h;
  
  bool validita;

  void move()
  {
    cout << "Inserire l e h su due righe diverse" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    cout << l << h;
    if ((l + h != l_2 + h_2 & l - h != l_2 - h_2) || antiJump(l, h, l_2, h_2,1)|| moveStart(l, h, l_2, h_2))
    {
      validita = false;
      cout << "Mossa non valida" << endl;
    }
    else
    {
      cout << "Mossa valida" << endl;
       if (M[l_2][h_2] == M[l][h]){
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
      }
    }
  }
};

class regina
{
private:
  double delt;
  double delh;

public:
  int l;
  int h;
  bool validita;

  void move()
  {

    cout << "Inserire l e h su due righe diverse" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    if (((l + h != l_2 + h_2 & l - h != l_2 - h_2 ) || (delh != 0 &  delt != 0)) || moveStart(l, h, l_2, h_2) || (antiJump(l, h, l_2, h_2,1)||antiJump(l, h, l_2, h_2,0)))
    {
      validita = false;
       cout << "Mossa non valida" << endl;
    }
    else
    {
       if (M[l_2][h_2] == M[l][h]){
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
      };
    }
  }
};

class re
{
private:
  double delt;
  double delh;

public:
  int l;
  int h;
  bool validita;

  void move()
  {
    cout << "Inserire l e h su due righe diverse" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    if (delh > 1 || delt > 1)
    {
      validita = false;
    }
    else
    {
       if (M[l_2][h_2] == M[l][h]){
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
      };
    }
  }
};

struct squadra
{
public:
  pedone P1;
  pedone P2;
  pedone P3;
  pedone P4;
  pedone P5;
  pedone P6;
  pedone P7;
  pedone P8;
  re KG;
  regina Q;
  alfiere B1;
  alfiere B2;
  torre T1;
  torre T2;
  cavallo C1;
  cavallo C2;
  void scelta()
  {
    bool flag1;
    do
    {
      flag1 = true;
      cout << "Quale pezzo vuoi muovere? (reset per pulire la tavola e ricominciare)" << endl;
      string typo;
      cin >> typo;
      // Non possiamo usare uno switch-case poichè typo è di tipo stringa
      if (typo == "pedone1")
      {
        P1.move();
      }
      else if (typo == "pedone2")
      {
        P2.move();
      }
      else if (typo == "pedone3")
      {
        P3.move();
      }
      else if (typo == "pedone4")
      {
        P4.move();
      }
      else if (typo == "pedone5")
      {
        P5.move();
      }
      else if (typo == "pedone6")
      {
        P6.move();
      }
      else if (typo == "pedone7")
      {
        P7.move();
      }
      else if (typo == "pedone8")
      {
        P8.move();
      }
      else if (typo == "torre1")
      {
        T1.move();
      }
      else if (typo == "torre2")
      {
        T2.move();
      }
      else if (typo == "alfiere1")
      {
        B1.move();
      }
      else if (typo == "alfiere2")
      {
        B2.move();
      }
      else if (typo == "cavallo1")
      {
        C1.move();
      }
      else if (typo == "cavallo2")
      {
        C2.move();
      }
      else if (typo == "regina")
      {
        Q.move();
      }
      else if (typo == "re")
      {
        KG.move();
      }
      else
      {
        cout << "COGLIONE!" << endl;
        flag1 = false;
      }
    } while (flag1 == false);
  }
};

squadra p1;
squadra p2;

void setLocStart()
{
  p1.P1.l = 1;
  p1.P1.h = 0;
  p1.P2.l = 1;
  p1.P2.h = 1;
  p1.P3.l = 1;
  p1.P3.h = 2;
  p1.P4.l = 1;
  p1.P4.h = 3;
  p1.P5.l = 1;
  p1.P5.h = 4;
  p1.P6.l = 1;
  p1.P6.h = 5;
  p1.P7.l = 1;
  p1.P7.h = 6;
  p1.P8.l = 1;
  p1.P8.h = 7;

  p1.T1.l = 0;
  p1.T1.h = 0;
  p1.T2.l = 0;
  p1.T2.h = 7;
  p1.C1.l = 0;
  p1.C1.h = 1;
  p1.C2.l = 0;
  p1.C2.h = 6;
  p1.KG.l = 0;
  p1.KG.h = 4;
  p1.Q.l = 0;
  p1.Q.h = 3;
  p1.B1.l = 0;
  p1.B1.h = 2;
  p1.B2.l = 0;
  p1.B2.h = 5;
///////////// ///////////// ///////////// ///////////// ///////////// /////////////
  p2.P1.l = 6;
  p2.P1.h = 0;
  p2.P2.l = 6;
  p2.P2.h = 1;
  p2.P3.l = 6;
  p2.P3.h = 2;
  p2.P4.l = 6;
  p2.P4.h = 3;
  p2.P5.l = 6;
  p2.P5.h = 4;
  p2.P6.l = 6;
  p2.P6.h = 5;
  p2.P7.l = 6;
  p2.P7.h = 6;
  p2.P8.l = 6;
  p2.P8.h = 7;
/////////////////////////
  p2.T1.l = 7;
  p2.T1.h = 0;
  p2.T2.l = 7;
  p2.T2.h = 7;
  p2.C1.l = 7;
  p2.C1.h = 1;
  p2.C2.l = 7;
  p2.C2.h = 6;
  p2.KG.l = 7;
  p2.KG.h = 3;
  p2.Q.l = 7;
  p2.Q.h = 4;
  p2.B1.l = 7;
  p2.B1.h = 2;
  p2.B2.l = 7;
  p2.B2.h = 5;
}

int main()
{
  setLocStart();
  //p1.P1.h = 0;
  for (int turni = 0; turni < 4; turni++)
  {
    cout << M << endl;
    p1.scelta();
    cout << M << endl;
    p2.scelta();
  }
  return 0;
}
