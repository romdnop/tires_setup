#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QtMath>

bool Print_Help(QTextStream *);
bool Calibrate_Rev(QTextStream *);
bool Enter_Tires(QTextStream *);
bool Check_Tires(QTextStream *);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream *s = new QTextStream(stdin);
    while(Print_Help(s));
    return a.exec();
}

bool Calibrate_Rev(QTextStream *s)
{
    QString value;

    float distanceGPS = 0;
    float distanceTruck = 0;
    float currentRevs = 0;
    float deltaInPercents = 0;

    std::cout << "Enter distance by GPS in km: ";
    value = s->readLine();
    distanceGPS = value.toInt();


    std::cout << "Enter distance by odometer in km: ";
    value = s->readLine();
    distanceTruck = value.toInt();


    std::cout << "Enter current revs\\km (Example: 230.1): ";
    value = s->readLine();
    currentRevs = value.toFloat();

    std::cout << "Distance by GPS: " << distanceGPS<<" Distance by truck: "<<distanceTruck<<"\n";
    deltaInPercents = static_cast <float>(((distanceTruck - distanceGPS)/((distanceGPS+distanceTruck)/2))*100);
    printf("Delta in percents: %.1f%\n", deltaInPercents);
    currentRevs = currentRevs + ((currentRevs*deltaInPercents)/100);


    std::cout << "New value revs\\km: " << value.setNum(currentRevs,'f',2).toStdString() << " units\n";


    return false;
}

bool Enter_Tires(QTextStream *s)
{
    std::cout << "Enter current tires height (in cm) (examples: 99.5, 99.0, 99): ";
    QString value = s->readLine();
    float tiresHeight = value.toFloat();
    float revsPerKm = 100000/(M_PI*tiresHeight);
    std::cout << "Revs\\km: " << value.setNum(revsPerKm,'f',2).toStdString() << " units\n";
    return false;
}


bool Check_Tires(QTextStream *s)
{
    std::cout << "Enter current rev\\km (example: 320.4): ";
    QString value = s->readLine();
    float revValue = value.toFloat();
    if(revValue >= 570 || revValue <= 0)
    {
        std::cout<< "Error in number format [Example: XXX.X]\n";
        return true;
    }
    //qDebug() << revValue;
    float tiresHeight = (100000/(3.14*revValue));
    tiresHeight = qFloor(tiresHeight/0.01 - 0.5)*0.01;
    std::cout << "Current tires height is equal to: " << value.setNum(tiresHeight,'f',2).toStdString() << "cm\n";
    return true;
}

bool Print_Help(QTextStream *s)
{
    std::cout << "\nSelect current action (Type number than press ENTER):\n[1]: Check current rev\\km value\n[2]: Enter new tires\n[3]: Callibrate exsited rev\\km ratio\n[0]: Exit\nSelect option: ";
    QString value =  s->readLine();

    switch(value.toInt())
    {
    case 0:
        return false;
    case 1:
        while(Check_Tires(s));
        break;
    case 2:
        while(Enter_Tires(s));
        break;
    case 3:
        while(Calibrate_Rev(s));
        break;
    default:
        std::cout<< "Unknown option";
    }
    return true;
}
