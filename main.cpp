#include <iostream>
#include <bitset> // for parsing into binary
#include <string>
#include <fstream> // for accessing to txt file
#include <conio.h> // for using keyboard
#include <iomanip> // for output
using namespace std;

bitset<24> makeBinary(int);                   // parses decimal to binary
bitset<24> addBinary(bitset<24>, bitset<24>); // finds the sum of two binary numbers
int remainderFDiv(bitset<24>, bitset<24>);    // finds the remainder of the division
void readProgram();                           // to read commands from txt file
string print(bitset<24>);                     // output a binary number with a space every 4 bits

// path to your txt file
string path_to_program = "program.txt";

// registers
bitset<24> R1 = 0b000000000000000000000000;
bitset<24> R2 = 0b000000000000000000000001;
bitset<24> R3 = 0b000000000000000000000010;
bitset<24> R4 = 0b000000000000000000000011;

int CC = 0; // commands counter register
int RS = 0; // register status (positive(0) or negative(1) number in the result)

string Ins; // command register

string operand1; // for the result
string operand2;
string operand3;

bitset<24> firstOperand;
bitset<24> secondOperand;

int main()
{
    // each new command is a new iteration of the loop
    for (;;)
    {
        // waiting for input before the first tact
        while (true)
        {
            if (kbhit())
            {
                getch();
                break;
            }
        }

        readProgram();

        // getting the value from the register
        if (operand2 == "R1")
        {
            firstOperand = R1;
        }
        else if (operand2 == "R2")
        {
            firstOperand = R2;
        }
        else if (operand2 == "R3")
        {
            firstOperand = R3;
        }
        else if (operand2 == "R4")
        {
            firstOperand = R4;
        }
        else
        {
            // if the operand is a number, not a register
            firstOperand = makeBinary(stoi(operand2));
        }

        // getting the value from the register
        if (operand3 == "R1")
        {
            secondOperand = R1;
        }
        else if (operand3 == "R2")
        {
            secondOperand = R2;
        }
        else if (operand3 == "R3")
        {
            secondOperand = R3;
        }
        else if (operand3 == "R4")
        {
            secondOperand = R4;
        }
        else
        {
            // if the operand is a number, not a register
            secondOperand = makeBinary(stoi(operand3));
        }

        // to stop the loop if the file is empty
        ifstream fi(path_to_program);
        if (fi.is_open())
        {
            if (fi.peek() == ifstream::traits_type::eof())
            {
                break;
            }

            fi.close();
        }

        // check if the specified command exists
        if (Ins != "set" && Ins != "add" && Ins != "mod")
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\nError! Unknown command.\n\n";

            // if not, then we skip this iteration
            continue;
        }
        // check if the result register exists
        if (operand1 != "R1" && operand1 != "R2" && operand1 != "R3" && operand1 != "R4")
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\nError! There is no such register.\n\n";

            // if not, then we skip this iteration
            continue;
        }

        // increase the command counter by one
        CC++;

        // output of information in the first tact
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nInstruction = " << Ins << " " << operand1 << " " << operand2 << " " << operand3 << endl
             << endl;
        cout << "R1 = " << print(R1);
        if (Ins != "set")
        {
            cout << setw(15) << "Ins = " << Ins << " | " << operand1 << " | " << print(firstOperand) << "| " << print(secondOperand) << endl;
        }
        else
        {
            cout << setw(15) << "Ins = " << Ins << " | " << operand1 << " | " << print(firstOperand) << endl;
        }
        cout << "R2 = " << print(R2);
        cout << setw(15) << "CC = " << CC << endl;
        cout << "R3 = " << print(R3);
        cout << setw(16) << "TC = 1" << endl;
        cout << "R4 = " << print(R4);
        cout << setw(15) << "RS = " << RS << endl;

        // waiting for input before the second tact
        while (true)
        {
            if (kbhit())
            {
                getch();
                break;
            }
        }

        if (Ins == "add")
        {
            if (operand1 == "R1")
            {
                R1 = addBinary(firstOperand, secondOperand);
            }
            else if (operand1 == "R2")
            {
                R2 = addBinary(firstOperand, secondOperand);
            }
            else if (operand1 == "R3")
            {
                R3 = addBinary(firstOperand, secondOperand);
            }
            else if (operand1 == "R4")
            {
                R4 = addBinary(firstOperand, secondOperand);
            }

            /*Here we do a sign check. Since the processor is 24-bit,
            the maximum decimal number that can be set is 8,388,607, the minimum is -8,388,608.
            If the number is greater than the maximum, then the numbers "go in a circle"
            and it becomes close to the minimum. For example: 8 388 607 + 1 = -8 388 608.
            The same and vice versa.*/
            if (addBinary(firstOperand, secondOperand).to_ulong() > 8388607)
            {
                RS = 1;
            }
            else if (addBinary(firstOperand, secondOperand).to_ulong() < 0 && addBinary(firstOperand, secondOperand).to_ulong() >= -8388608)
            {
                RS = 1;
            }
            else
            {
                RS = 0;
            }
        }
        else if (Ins == "set")
        {
            if (operand1 == "R1")
            {
                R1 = firstOperand;
            }
            else if (operand1 == "R2")
            {
                R2 = firstOperand;
            }
            else if (operand1 == "R3")
            {
                R3 = firstOperand;
            }
            else if (operand1 == "R4")
            {
                R4 = firstOperand;
            }

            // sign check
            if (firstOperand.to_ulong() > 8388607)
            {
                RS = 1;
            }
            else if (firstOperand.to_ulong() < 0 && firstOperand.to_ulong() >= -8388608)
            {
                RS = 1;
            }
            else
            {
                RS = 0;
            }
        }
        else if (Ins == "mod")
        {
            if (operand1 == "R1")
            {
                R1 = remainderFDiv(firstOperand, secondOperand);
            }
            else if (operand1 == "R2")
            {
                R2 = remainderFDiv(firstOperand, secondOperand);
            }
            else if (operand1 == "R3")
            {
                R3 = remainderFDiv(firstOperand, secondOperand);
            }
            else if (operand1 == "R4")
            {
                R4 = remainderFDiv(firstOperand, secondOperand);
            }

            // no check is needed because division with a remainder always gives 0 or more
            RS = 0;
        }

        // output of information in the second tact
        cout << "\n\nInstruction = " << Ins << " " << operand1 << " " << operand2 << " " << operand3 << endl
             << endl;
        cout << "R1 = " << print(R1);
        if (Ins != "set")
        {
            cout << setw(15) << "Ins = " << Ins << " | " << operand1 << " | " << print(firstOperand) << "| " << print(secondOperand) << endl;
        }
        else
        {
            cout << setw(15) << "Ins = " << Ins << " | " << operand1 << " | " << print(firstOperand) << endl;
        }
        cout << "R2 = " << print(R2);
        cout << setw(15) << "CC = " << CC << endl;
        cout << "R3 = " << print(R3);
        cout << setw(16) << "TC = 2" << endl;
        cout << "R4 = " << print(R4);
        cout << setw(15) << "RS = " << RS << endl
             << endl;
    }

    return 0;
}

bitset<24> makeBinary(int decimal)
{
    return bitset<24>(decimal);
}

bitset<24> addBinary(bitset<24> a, bitset<24> b)
{
    bitset<24> result;
    bool carry = 0; // carrying a digit of a number

    for (size_t i = 0; i < result.size(); i++)
    {
        // we add the corresponding bits of the two numbers and carry
        bool sum = a[i] ^ b[i] ^ carry;
        result[i] = sum;
        // we determine the carry for the next digit
        carry = (a[i] & b[i]) | (a[i] & carry) | (b[i] & carry);
    }

    return result;
}

int remainderFDiv(bitset<24> a, bitset<24> b)
{
    // parsing binary to decimal
    unsigned long new_a = a.to_ulong();
    unsigned long new_b = b.to_ulong();

    return new_a % new_b;
}

void readProgram()
{
    ifstream file(path_to_program);

    file >> Ins >> operand1 >> operand2 >> operand3;

    /*the following is needed to remove the first line from the file
    so that the same command is not read each time when the function is called*/
    ofstream newfile(path_to_program);

    string line;
    while (getline(file, line))
    {
        newfile << line << "\n";
    }

    file.close();
    newfile.close();
}

string print(bitset<24> bits)
{
    string str = bits.to_string();
    string result;
    for (int i = 0; i < 24; i++)
    {
        result += str[i];
        if ((i + 1) % 4 == 0)
        {
            result += " ";
        }
    }
    return result;
}
