#include "char_to_int.cc"
#include "ram.cc"
#include "split_instruction.cc"
#include "utils.cc"

void interpretInstructions(string instruction, int *&ram)
{
    char *instructions = splitInstruction(instruction);
    int main = charToInt(instructions[0]);
    int num1 = charToInt(instructions[1]);
    int num2 = charToInt(instructions[2]);

    switch (main) {
        case 1: // 100 - halt(we assume session terminated)
                // delete[] ram;
                // delete[] instructions;
                // cout << "Session terminated\n";
                // exit(0);
        case 2: // 2dn - set register d to n
            alterRAM(num1, num2, ram);
            break;
        case 3: // 3dn - add n to register d
            alterRAM(num1, (num2 + ram[num1]), ram);
            break;
        case 4: // 4dn - multiply register d by n
            alterRAM(num1, (num2 * ram[num1]), ram);
            break;
        case 5: // 5ds - set register d to the value of register s
            alterRAM(num1, ram[num2], ram);
            break;
        case 6: // 6ds - add the value of register s to register d
            alterRAM(num1, (ram[num1] + ram[num2]), ram);
            break;
        case 7: // 7ds - multiply register d by the value of register s
            alterRAM(num1, (ram[num1] * ram[num2]), ram);
            break;
        case 8: // 8da - set register d to the value in RAM whose address is in
                // register a
            alterRAM(num1, ram[num2], ram);
            break;
        case 9: // 9sa - set the value in RAM whose address is in register a to
                // that of register s
            alterRAM(num2, ram[num1], ram);
            break;
        case 0: // 0ds - goto the location in register d unless register s
                // contains 0
            // assume goto d unless s contains 0
            if (ram[num2] == 0) {
                // goto s
            } else {
                // goto d
            }
            break;
    }

    delete[] instructions;
}

void testInterpretInstructions_9()
{
    int *expected = initializeRAM();
    expected[3] = 4;
    expected[8] = 5;
    expected[3] = expected[8];
    int *actual = initializeRAM();
    actual[3] = 4;
    actual[8] = 5;
    interpretInstructions("983", actual);
    printTestMessage("9", equals(expected, actual));
    delete[] expected;
    delete[] actual;
}

void testInterpretInstructions_8()
{
    int *actual = initializeRAM();
    actual[0] = 3;
    actual[4] = actual[0];
    int *expected = initializeRAM();
    expected[0] = 3;
    interpretInstructions("840", expected);
    printTestMessage("8", equals(actual, expected));
    delete[] actual;
    delete[] expected;
}

void testInterpretInstructions_7()
{
    int *actual = initializeRAM();
    actual[0] = 2;
    actual[3] = 4;
    actual[0] = actual[0] * actual[3];
    int *expected = initializeRAM();
    expected[0] = 2;
    expected[3] = 4;
    interpretInstructions("703", expected);
    printTestMessage("7", equals(actual, expected));
    delete[] actual;
    delete[] expected;
}

void testInterpretInstructions_6()
{
    int *actual = initializeRAM();
    actual[3] = 2;
    actual[5] = 4;
    actual[5] = actual[3] + actual[5];
    int *expected = initializeRAM();
    expected[3] = 2;
    expected[5] = 4;
    interpretInstructions("653", expected);
    printTestMessage("6", equals(expected, actual));
    delete[] expected;
    delete[] actual;
}

void testInterpretInstructions_5()
{
    int *actual = initializeRAM();
    actual[2] = 3;
    actual[5] = actual[2];
    int *expected = initializeRAM();
    expected[2] = 3;
    interpretInstructions("552", expected);

    printTestMessage("5", equals(actual, expected));

    delete[] actual;
    delete[] expected;
}

void testInterpretInstructions_4()
{
    int *ram = initializeRAM();
    ram[2] = 10;
    int *actual = initializeRAM();
    actual[2] = 2;
    interpretInstructions("425", actual);

    printTestMessage("4", equals(ram, actual));

    delete[] ram;
    delete[] actual;
}

void testInterpretInstructions_2()
{
    int *ram = initializeRAM();
    ram[3] = 5;
    int *actual = initializeRAM();
    interpretInstructions("235", actual);

    printTestMessage("2", equals(ram, actual));

    delete[] ram;
    delete[] actual;
}

void testInterpretInstructions_3()
{
    int *expected = initializeRAM();
    expected[3] = 5;
    int *actual = initializeRAM();
    actual[3] = 2;
    interpretInstructions("333", actual);

    printTestMessage("3", equals(expected, actual));

    delete[] expected;
    delete[] actual;
}

int main(int argc, char **argv)
{
    // testInterpretInstructions_2();
    // testInterpretInstructions_3();
    // testInterpretInstructions_4();
    // testInterpretInstructions_5();
    // testInterpretInstructions_6();
    // testInterpretInstructions_7();
    // testInterpretInstructions_8();
    // testInterpretInstructions_9();
}
