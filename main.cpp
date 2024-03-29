#include <iostream>
#include "Matrix.h"
#include <cmath>
using namespace std;

int l;
int h;
int l_2;
int h_2;
int nummoss =0;
int var;

// Definiamo i delta degli spostamenti dei pezzi
double delt;
double delh;

bool checkmate = false;

// Definiamo la tavola di partenza
string set[64] = {"T01", "C01", "A01", "Q0", "L0", "A02", "C02", "T02",
                  "P01", "P02", "P03", "P04", "P05", "P06", "P07", "P08",
                  "0", "0", "0", "0", "0", "0", "0", "0",
                  "0", "0", "0", "0", "0", "0", "0", "0",
                  "0", "PP", "0", "0", "0", "0", "0", "0",
                  "0", "0", "0", "0", "0", "0", "0", "0",
                  "P11", "P12", "P13", "P14", "P15", "P16", "P17", "P18",
                  "T11", "C11", "A11", "F1", "Q1", "A12", "C12", "T12"};

// Carichiamo la tavola in un oggetto Matrice
Matrix<string> M(8, 8, set);
void checkMate()
{
  int p = 0;
  for (int i = 0; i < 8; i++)
  {

    for (int a = 0; a < 8; a++)
    {
      if (M[i][a] != "L0" & M[i][a] != "F1")
      {
        p++;
      }
    }
  }
  if (p != 62)
  {
    checkmate = true;
    cout << "Scacco Matto!!" << endl;
  }
}

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
    
  }

  return isNotValid;
}

bool antiJump(int l, int h, int l_2, int h_2, int flagAntiJump)
{
  bool antiJumpbool;
  double  delt = fabs(l - l_2);
  double delh = fabs(h - h_2);
  int delx = l_2 - l;
  int dely = h_2 - h;
  int k;
  int j;

  if (flagAntiJump == 0)
  {

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
      while (M[l][j] != M[l][h])
      {
        cout << l << j << endl; 
        if (M[l][j] == "0")
        {
          cout << "j:" << M[l][j] << endl;
          if (h_2 < h)
          {
            cout << "J:+" << endl;
            j++;
          }
          else
          {
            cout << "J:-" << endl;
            j--;
          }
          cout << "j:" << M[l][j] << endl;
        }
        else
        {
          cout << "non saltare nessuno" << M[l][j] << endl;
          antiJumpbool = true;
          break;
        }
      }
    }
  }
  else if (flagAntiJump == 1)
  {
    cout << "dely" << dely << "delx" << delx << endl;
    int mover0;
    int mover1;
    //////////////////////////////////////////////////////////
    if (dely * delx > 0)
    {

      if (dely < 0)
      {
        cout << "sinistra in alto" << endl;
        k = l_2 + 1;
        j = h_2 + 1;
        mover0 = 1;
        mover1 = 1;
      }
      else
      {
        cout << "destra in basso" << endl;
        k = l_2 - 1;
        j = h_2 - 1;
        mover0 = -1;
        mover1 = -1;
      }
    }
    else
    {
      if (dely > 0)
      {
        cout << "destra in alto" << endl;
        k = l_2 + 1;
        j = h_2 - 1;
        mover0 = +1;
        mover1 = -1;
      }
      else
      {
        cout << "sinistra in basso" << endl;
        k = l_2 - 1;
        j = h_2 + 1;
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
    cout << "regina" << endl;
  }
  return antiJumpbool;
}

// Definizione della classe pedone che prevede gli spostamenti di questa tipologia di pezzi
class pedone
{
public:
  int l;
  int h;
  bool validita;
  bool validita2;
  bool validita3;
  
  void move()
  {
    cout << "Inserire r e c  su due righe diverse ( righe 0,7 colonne 0,7)" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    
    if (nummoss == 1 ||nummoss == 2 ){
      var = 2;
    }
    else
    {
      var = 1;

    }
    if (delh != 0 || delt > var)
    {
      
      validita = false;
    }
    else
    {
      validita = true;
    }
    if (delh != 1 || delt != 1)
    {
     
      validita2= false;
    }
    else
    {
      
      validita2= true;
    }
    if (M[l_2][h_2] == "0"){
      validita3 = true;
    }
    else 
    {
      validita3= false;
    }

    if (validita & validita3 || (validita2 & (!validita3 & !moveStart(l, h, l_2, h_2))))
    {
       if (M[l_2][h_2] == M[l][h])
      {
        cout << "Mossa non valida" << endl;
      }
      else
      {
        cout << "Mossa valida" << endl;
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
        system("clear");
      }
     
    }
    else
    { 
      cout << "Mossa non valida" << endl;
     
     
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
    cout << "Inserire r e c  su due righe diverse ( righe 0,7 colonne 0,7)" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    if ((delh != 0 & delt != 0) || antiJump(l, h, l_2, h_2, 0) || moveStart(l, h, l_2, h_2))
    {
      cout << "Mossa non valida" << endl;
    }
    else
    {
      cout << "Mossa valida" << endl;
      if (M[l_2][h_2] == M[l][h])
      {
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
        system("clear");
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
    cout << "Inserire r e c  su due righe diverse ( righe 0,7 colonne 0,7)" << endl;
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
      if (M[l_2][h_2] == M[l][h])
      {
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
        system("clear");
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
    cout << "Inserire r e c  su due righe diverse ( righe 0,7 colonne 0,7)" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    cout << l << h;
    if ((l + h != l_2 + h_2 & l - h != l_2 - h_2) || antiJump(l, h, l_2, h_2, 1) || moveStart(l, h, l_2, h_2))
    {
      validita = false;
      cout << "Mossa non valida" << endl;
    }
    else
    {
      cout << "Mossa valida" << endl;
      if (M[l_2][h_2] == M[l][h])
      {
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
        system("clear");
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

    cout << "Inserire r e c  su due righe diverse ( righe 0,7 colonne 0,7)" << endl;
    cin >> l_2;
    cin >> h_2;
    delt = fabs(l - l_2);
    delh = fabs(h - h_2);
    if (((l + h != l_2 + h_2 & l - h != l_2 - h_2) || (delh != 0 & delt != 0)) || moveStart(l, h, l_2, h_2) || (antiJump(l, h, l_2, h_2, 1) || antiJump(l, h, l_2, h_2, 0)))
    {
      validita = false;
      cout << "Mossa non valida" << endl;
    }
    else
    {
      if (M[l_2][h_2] == M[l][h])
      {
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
        system("clear");
      }
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
    cout << "Inserire r e c  su due righe diverse ( righe 0,7 colonne 0,7)" << endl;
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
      if (M[l_2][h_2] == M[l][h])
      {
        cout << "Mossa non valida" << endl;
      }
      else
      {
        M[l_2][h_2] = M[l][h];
        M[l][h] = "0";
        l = l_2;
        h = h_2;
        system("clear");
      }
    }
  }
};

struct squadra
{

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
      cout << "Quale pezzo vuoi muovere? ( E  per uscire )" << endl;
      char typo;
      int num;
      cin >> typo;
      switch (typo)
      {
      case 'P':
        cin >> num;
        switch (num)
        {
        case 1:
          cout << "P1" << endl;
          P1.move();
          break;
        case 2:
          cout << "P2" << endl;
          P2.move();
          break;
        case 3:
          cout << "P3" << endl;
          P3.move();
          break;
        case 4:
          cout << "P4" << endl;
          P4.move();
          break;
        case 5:
          cout << "P5" << endl;
          P5.move();
          break;
        case 6:
          cout << "P6" << endl;
          P6.move();
          break;
        case 7:
          cout << "P7" << endl;
          P7.move();
          break;
        case 8:
          cout << "P8" << endl;
          P8.move();
          break;
        default:
          break;
        }      
        break;
      case 'T':
        cin >> num;
        switch (num)
        {
        case 1:
          cout << "T1" << endl;
          T1.move();
          break;
        case 2:
          cout << "T2" << endl;
          T2.move();
          break;
        default:
          break;
        }
        break;
      case 'A':
        cin >> num;
        switch (num)
        {
        case 1:
          cout << "A1" << endl;
          B1.move();
          break;
        case 2:
          cout << "A2" << endl;
          B2.move();
          break;
        default:
          break;
        }
        break;
      case 'C':
        cin >> num;
        switch (num)
        {
        case 1:
          cout << "C1" << endl;
          C1.move();
          break;
        case 2:
          cout << "C2" << endl;
          C2.move();
          break;
        default:
          break;
        }
        break;
      case 'K':
        cout << "re" << endl;
        KG.move();
        break;
      case 'Q':
        cout << "regina" << endl;
        Q.move();
        break;
      case 'E':
        cout << "Exit in corso...." << endl;
      
        checkmate = true;
        break;
      default:
        cout << "Riprova!" << endl;
        flag1 = false;
        break;
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
 
  p2.T1.l = 7;
  p2.T1.h = 0;
  p2.T2.l = 7;
  p2.T2.h = 7;
  p2.C1.l = 7;
  p2.C1.h = 1; 
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
  while (!checkmate)
  {
    nummoss++;
    
    cout << M << endl;
    p1.scelta();
    checkMate();
    if (checkmate)
    {
      break;
    }
   
    cout << M << endl;
    nummoss++;
    p2.scelta();
    checkMate();
  }
  _Exit(0);
}
