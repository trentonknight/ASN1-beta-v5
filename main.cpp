#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

void getTicket(ifstream& logTicket, ofstream& logCar, ofstream& logQuad);
void getFine(double& fine, double& fee);
void sendForViewer(double& totalAmt, int fines);


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
    double sLimit;
    double sBroken;
    double fine, fee, TotalFines;
    int count;
    char ch;

    while(logTicket)
    {

        logCar << endl;
        lastPlateRecord.assign(inputPlate);
        logTicket >> inputPlate;
        logTicket.get(ch);

        if (lastPlateRecord.compare(inputPlate) != 0)
        {
            logCar << inputPlate << "\t";
            cout << inputPlate << "\t";
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
            sendForViewer(TotalFines, count);


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

void sendForViewer(double& totalAmt, int fines)
{  
    cout << fines << "\t" << totalAmt << endl;  
}
