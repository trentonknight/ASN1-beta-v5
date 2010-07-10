#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

void getTicket(ifstream& logTicket, ofstream& logCar, ofstream& logQuad);
void getFine(double& fine, double& fee);
void printScreen();

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
    logQuad.close();

    return 0;
}

void getTicket(ifstream& logTicket,ofstream& logCar, ofstream& logQuad)
{
    string inputPlate;
    string lastPlateRecord;
    string inputQuad;
    string outPut;
    double sLimit;
    double sBroken;
    double fine, fee, TotalFines, TotalTotalFines;
    int count, lastCount;
    char ch;

    while(logTicket)
    {
        lastCount = 0;
        logCar << endl;
        lastPlateRecord.assign(inputPlate);
        logTicket >> inputPlate;
        logTicket.get(ch);
        TotalTotalFines = TotalFines + TotalTotalFines;

        if (lastPlateRecord.compare(inputPlate) != 0)
        {
            logCar << inputPlate << "\t";
            count = 0;
            TotalFines = 0.0;       
        }
        while((ch != '\n') && logTicket)
        {
            logTicket >> inputQuad >> sLimit >> sBroken;
            fine = sBroken - sLimit;
            getFine(fine, fee);
            logQuad << inputQuad << "\t" << fee << endl;
            logCar << setw(13) << fee;
            logTicket.get(ch);
            TotalFines = fee + TotalFines;
            count++;
            lastCount++;
        }
        if(count == lastCount)
        {
          printScreen();
          cout << inputPlate << "\t" << count << "\t\t"<< "$" << TotalFines << endl;
        }

    }
     cout << "Total District Fines: \t\t$" << TotalTotalFines << endl;

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
   cout << fixed << showpoint << setprecision(2) << endl;
   cout << "License\t" << "Number Tickets\t" << "Total Fines" << endl;
}
