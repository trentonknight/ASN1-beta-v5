#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

void getTicket(ifstream& logTicket, ofstream& logCar, ofstream& logQuad);
void getFine(double& fine, double& fee);
void printScreen();
void pauseSystem();


int main()
{
    ifstream logTicket;
    ofstream logCar;
    ofstream logQuad;
    logTicket.open("TICKETS.TXT");
    logCar.open("CARFINES.TXT");
    logCar << fixed << showpoint << setprecision(2);
    logQuad.open("QUADFINES.TXT");
    logQuad << fixed << showpoint << setprecision(2);

    if(!logTicket)
    {
        cout << "Unable to open TICKETS.TXT." << endl;
        cout << "Verify file exists." << endl;
        return 1;
    }
    getTicket(logTicket, logCar, logQuad);
    logTicket.close();
    logCar.close();
    printScreen();
    logQuad.close();

    return 0;
}

void getTicket(ifstream& logTicket,ofstream& logCar, ofstream& logQuad)
{
    string inputPlate;
    string lastPlateRecord;
    string inputQuad;
    double sLimit;
    double sBroken;
    double fine, fee;
    int lastCount;
    char ch;

    while(logTicket)
    {
        lastCount = 0;
        logCar << endl;
        lastPlateRecord.assign(inputPlate);
        logTicket >> inputPlate;
        logTicket.get(ch);

        if (lastPlateRecord.compare(inputPlate) != 0)
        {
            logCar << inputPlate << "\t";
        }
        while((ch != '\n') && logTicket)
        {
            logTicket >> inputQuad >> sLimit >> sBroken;
            fine = sBroken - sLimit;
            getFine(fine, fee);
            logQuad << inputQuad << "\t" << fee << endl;
            logCar << setw(13) << fee;
            logTicket.get(ch);
        }
    }  
}

void getFine(double& fine, double& fee)
{
    cout << fixed << showpoint << setprecision(2) << endl;

    if (fine <= 10){
        fee = fine * 2.25;
    }
    else if (fine > 10 && fine <= 20){
        fee = fine * 3.50;
    }
    else if (fine > 20){
        fee = fine * 5.00;
    }
    else {
    }

}

void printScreen()
{
    ifstream printTick;
    string plate;
    char ch;
    double fine, total;
    int Tfines;
    printTick.open("CARFINES.TXT");

    cout << fixed << showpoint << setprecision(2) << endl;
    cout << "License\t" << "Number Tickets\t" << "Total Fines" << endl;

    while(printTick >> plate)
    {
        printTick.get(ch);
        fine = 0;
        total = 0;
        Tfines = 0;
        cout << plate << "\t";


        while((ch !='\n') && printTick >> fine)
        {
            printTick.get(ch);
            total = fine + total;
            Tfines++;

        }
        cout << Tfines << "\t" << "$" << total << endl;
        cout << "_" << setw(49) << setfill('_') << "_" << endl;
    }
    printTick.close();

}

void pauseSystem() {

#ifdef __WIN32
    system("PAUSE");
#endif
#ifdef __WIN64
    system("PAUSE");
#endif
#ifdef linux
    cout << "Press ENTER to continue... " << flush;
    cin.ignore( 1, '\n' );
#endif

}
