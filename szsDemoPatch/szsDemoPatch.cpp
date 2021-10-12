// szsDemoPatch.cpp : Patches szs files into the Sunshine Demo Disc
//i apologize to anyone reading this code lol

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

bool patchFile(std::string szs, std::string tgc, std::string level, std::string patchName);
bool checkFiles(std::string szs, std::string tgc);

struct level
{
    long startOffset;
    long endOffset;
    long nameOffset;
    long nameLength;
    long nameOrder;
    bool canGoOver;
};

//argv[0] = this exe, argv[1] = tgc, argv[2] = szs, argv[3] = level to patch over, argv[4] = name of patching level
int main(int argc, char* argv[])
{
    using namespace::std;
    cout << "\n\n\n>>Running!<<\n";

    //checks to make sure argv[1] and argv[2] are the correct files
    if (!checkFiles(argv[2], argv[1]))
        return 1;

    //calls patchFile() (should be self explanitory)
    //argv[2] = tgc, argv[1] = szs, argv[3] = level name
    //if patchFile returns false, then the program stops
    if (!patchFile(argv[2], argv[1], argv[3], argv[4]))
        return 1;

    cout << "\n>>The TGC Should be Patched Succfully! Program Stopping!<<\n";
}



bool patchFile(std::string szs, std::string tgc, std::string levelStr, std::string patchName)
{
    //sets values to each level
    const level bianco0 = { 0x0E5035A0, 0x0E81FD30, 0x010859C, 11, 1, true };
    const level bianco1 = { 0x0E81FD34, 0x0EB0EDB9, 0x01085A8, 11, 2, true };
    const level biancoBoss = { 0x0EB0EDBC, 0x0EC49A65, 0x01085B4, 14, 3, true };
    const level coro_ex1 = { 0x0EC49A68, 0x0ECF779C, 0x01085C3, 12, 4, true };
    const level mamma1 = { 0x0ECF77A0, 0x0F04A0DB, 0x01085D0, 10, 5, true };
    const level mamma2 = { 0x0F04A0DC, 0x0F38EFC4, 0x01085DB, 10, 6, false };
    const level ricco0 = { 0x0F3E2DE4, 0x0F6E12A3, 0x01085F1, 10, 8, true };
    const level ricco8 = { 0x0F6E12A4, 0x0F9CBE9D, 0x01085FC, 10, 9, false };

    //figures out which level the player chose
    level chosenLevel = bianco0;
    if (strcmp(levelStr.c_str(), "bianco0") == 0 || strcmp(levelStr.c_str(), "bianco0.szs") == 0 || strcmp(levelStr.c_str(), "b0") == 0 )
        chosenLevel = bianco0;
    if (strcmp(levelStr.c_str(), "bianco1") == 0 || strcmp(levelStr.c_str(), "bianco1.szs") == 0 || strcmp(levelStr.c_str(), "b1") == 0)
        chosenLevel = bianco1;
    if (strcmp(levelStr.c_str(), "biancoBoss") == 0 || strcmp(levelStr.c_str(), "biancoBoss.szs") == 0 || strcmp(levelStr.c_str(), "bb") == 0)
        chosenLevel = biancoBoss;
    if (strcmp(levelStr.c_str(), "coro_ex1") == 0 || strcmp(levelStr.c_str(), "coro_ex1.szs") == 0 || strcmp(levelStr.c_str(), "ce1") == 0)
        chosenLevel = coro_ex1;
    if (strcmp(levelStr.c_str(), "mamma1") == 0 || strcmp(levelStr.c_str(), "mamma1.szs") == 0 || strcmp(levelStr.c_str(), "m1") == 0)
        chosenLevel = mamma1;
    if (strcmp(levelStr.c_str(), "mamma2") == 0 || strcmp(levelStr.c_str(), "mamma2.szs") == 0 || strcmp(levelStr.c_str(), "m2") == 0)
        chosenLevel = mamma2;
    if (strcmp(levelStr.c_str(), "ricco0") == 0 || strcmp(levelStr.c_str(), "ricco0.szs") == 0 || strcmp(levelStr.c_str(), "r0") == 0)
        chosenLevel = ricco0;
    if (strcmp(levelStr.c_str(), "ricco8") == 0 || strcmp(levelStr.c_str(), "ricco8.szs") == 0 || strcmp(levelStr.c_str(), "r8") == 0)
        chosenLevel = ricco8;

    //opens the source file(szs)
    std::fstream src(szs, std::ios::binary | std::ios::in);
    if (src.is_open()){}
        //printf("%s\n", "SRC OPEN");
    else
    {
        printf("%s\n", "SRC NOT OPEN! TERMINATING!");
        return false;
    }

    //opens the destination file(tgc)(just for reading)
    std::fstream dest(tgc, std::ios::binary | std::ios::in);
    if (dest.is_open()){}
        //printf("%s\n", "DEST OPEN");
    else
    {
        printf("%s\n", "DEST NOT OPEN! TERMINATING!");
        return false;
    }

    //gets the length of the source file
    src.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize srcLength = src.gcount();
    src.clear();
    src.seekg(0, std::ios_base::beg);

    //if the source file is longer in bytes than the file it's patching over, this prompt makes sure that's understood by the user
    char yesOrNo[1] = { 'x' };

    if (chosenLevel.endOffset - chosenLevel.startOffset < srcLength)
    {
        if (chosenLevel.canGoOver == false)
        {
            std::cout << "\nYour given file will overwrite portions of the next level! Normally that's ok, but not in this case because of what" <<
                " it's overwriting! It's reccomended you either try again with a smaller .szs file, or don't patch over \"mamma2\" or " <<
                "\"ricco8!\" The program will now terminate!(sorry)";
            return false;
        }
        else
        {
            while (true)
            {
                std::cout << "\nYour given file will (safely) overwrite portions of the next level! Is that ok? [y/n]\n";
                std::cin >> yesOrNo[0];
                std::cout << "Answer: " << yesOrNo[0] << std::endl;
                if (yesOrNo[0] == 'y' || yesOrNo[0] == 'Y')
                    break;
                else if (yesOrNo[0] == 'n' || yesOrNo[0] == 'N')
                {
                    printf("\nEnding program! (User answered no)");
                    return false;
                }
                else std::cout << "\nNot a valid answer! Trying again!";
            }
        }
    }

    //creates the dynamic source buffer
    char* srcBufferPtr = new char[srcLength];

    //creates the destination buffer(too big for heap)
    char* destBufferPtr = new char[0x10E30000];

    //reads the source file into the source buffer
    src.read(srcBufferPtr, srcLength);

    //reads the destination file into the destination buffer
    dest.read(destBufferPtr, 0x10E30000);

    dest.close();

    //patches srcBufferPtr into destBufferPtr
    memcpy(destBufferPtr + chosenLevel.startOffset, srcBufferPtr, srcLength);

    yesOrNo[0] = { 'x' };

    //patches the level name into desBufferPtr
    int patchNameLength = patchName.length();
    //printf("%s%i\n", "patchNameLength: ", patchNameLength);    
    if (patchNameLength > chosenLevel.nameLength)
    {
        //printf("%s\n", "patchNameLength exceeds nameLength!");
        memcpy(destBufferPtr + chosenLevel.nameOffset, &patchName[0], patchNameLength);
        if (!chosenLevel.canGoOver)
        {
            printf("%s%s%s","\nYour given name will overwrite portions of the next name! Normally that's ok, but not in this case because of what",
                " it's overwriting! It's reccomended you either try again with a smaller name, or don't patch over \"mamma2\" or ",
                "\"ricco8!\" The program will now terminate!(sorry)");
            return false;
        }

        while (true)
        {
            std::cout << "\nYour given file will (safely) overwrite portions of the next name! Is that ok? [y/n]\n";
            std::cin >> yesOrNo[0];
            std::cout << "Answer: " << yesOrNo[0] << std::endl;
            if (yesOrNo[0] == 'y' || yesOrNo[0] == 'Y')
            {
                //closes and reopens dest(to truncate it, which cant be done before it's copied into the buffer)
                dest.open(tgc, std::ios::binary | std::ios::out | std::ios::trunc);
                if (dest.is_open()){}
                    //printf("%s\n", "DEST REOPENED");
                else
                {
                    printf("%s\n", "DEST NOT REOPENING! TERMINATING!");
                    return false;
                }
                break;
            }
            else if (yesOrNo[0] == 'n' || yesOrNo[0] == 'N')
            {
                printf("\nEnding program! (User answered no)");
                return false;
            }
            else std::cout << "\nNot a valid answer! Trying again!";
        }

        int memCount = 0;
        while (true)
        {
            if (destBufferPtr[chosenLevel.nameOffset + patchNameLength + memCount] != '\0')
            {
                memcpy(destBufferPtr + chosenLevel.nameOffset + patchNameLength + memCount, "\0", 1);
            }
            else break;
            memCount++;
        }
    }
    else if (patchNameLength < chosenLevel.nameLength)
    {
        dest.open(tgc, std::ios::binary | std::ios::out | std::ios::trunc);
        if (dest.is_open()){}
           // printf("%s\n", "DEST REOPENED");
        else
        {
            printf("%s\n", "DEST NOT REOPENING! TERMINATING!");
            return false;
        }
        memcpy(destBufferPtr + chosenLevel.nameOffset, &patchName[0], patchNameLength);

        int memCount = 0;
        while (true)
        {
            if (destBufferPtr[chosenLevel.nameOffset + patchNameLength + memCount] != '\0')
            {
                memcpy(destBufferPtr + chosenLevel.nameOffset + patchNameLength + memCount, "\0", 1);
            }
            else break;
            memCount++;
        }
    }
    else if (patchNameLength == chosenLevel.nameLength)
    {
        //closes and reopens dest(to truncate it, which cant be done before it's copied into the buffer)
        dest.open(tgc, std::ios::binary | std::ios::out | std::ios::trunc);
        if (dest.is_open()){}
            //printf("%s\n", "DEST REOPENED");
        else
        {
            printf("%s\n", "DEST NOT REOPENING! TERMINATING!");
            return false;
        }
        //printf("%s\n", "patchNameLength equals nameLength!");
        memcpy(destBufferPtr + chosenLevel.nameOffset, &patchName[0], patchNameLength);
    }


    //deallocates and unpoints srcBufferPtr
    delete srcBufferPtr;
    srcBufferPtr = nullptr;

    //writes destBufferPtr to file
    dest.write(destBufferPtr, 0x10E30000);

    dest.close();
    src.close();

    return true;
}

//returns false if either the tgc or the szs fail to "authenticate."
//it's a failsafe to make sure a file that isn't zz_marioTaiken5.tgc isn't accidently altered
bool checkFiles(std::string szs, std::string tgc)
{
    using namespace::std;

    //checks to make sure the szs exists and is open
    fstream szsCheck(szs, ios::binary | ios::in);
    if (szsCheck.is_open()){}
       // printf("%s\n", "\nszsCheck is OPEN!");
    else
    {
        printf("%s\n", "\nszsCheck is NOT open! Terminating!");
        return false;
    }

    //reads part of the szs into a char array
    char szsRead[0x16] = "null";
    szsCheck.read(szsRead, 0x15);

    //checks for the signature "Yaz0" and "RARC" at the beginning of every szs
    if (szsRead[0x0] != 'Y' || szsRead[0x1] != 'a' || szsRead[0x2] != 'z' || szsRead[0x3] != '0')
    {
        printf("The .szs failed to authenticate(Yaz0)! Terminating!");
        return false;
    }
    else if (szsRead[0x11] != 'R' || szsRead[0x12] != 'A' || szsRead[0x13] != 'R' || szsRead[0x14] != 'C')
    {
        printf("The .szs failed to authenticate(RARC)! Terminating!");
        return false;
    }

    //closes the szs
    szsCheck.close();

    //checks to make sure the tgc exists and is open
    fstream tgcCheck(tgc, ios::binary | ios::in);
    if (tgcCheck.is_open()){}
    //    printf("%s\n", "\ntgcCheck is OPEN!");
    else
    {
        printf("%s\n", "\ntgcCheck is NOT open! Terminating!");
        return false;
    }

    //reads part of the tgc into a char array
    char tgcRead[0x41] = "null";
    tgcCheck.read(tgcRead, 0x40);

    //checks for certain characters that are at the beginning of the tgc
    if (tgcRead[0x2] != '8' || tgcRead[0x17] != 'z' || tgcRead[0x1B] != 'z' || tgcRead[0x25] != 'O'  ||
        tgcRead[0x27] != 't' || tgcRead[0x2A] != 'g' || tgcRead[0x34] != 'F' || tgcRead[0x35] != 'r' || tgcRead[0x37] != 't')
    {
        printf("The .tgc failed to authenticate(header)! Terminating!");
        return false;
    }

    printf("\n===============================================================\n== Checking the tgc's filesize! This may take a few seconds! ==\n===============================================================\n");

    //checks if the tgc is the same size as it should be(0x10E30000 bytes, but this program detects it at 0x10E2FFC0 for some reason...)
    tgcCheck.ignore(numeric_limits<streamsize>::max());
    streamsize tgcLength = tgcCheck.gcount();
    tgcCheck.clear();
    tgcCheck.seekg(0, ios_base::beg);

    if (tgcLength != 0x10E2FFC0)
    {
        printf("The .tgc failed to authenticate(length)! Terminating!");
        return false;
    }    

    printf("\n--The .tgc and .szs authenticated! Moving on!--\n");
    return true;
}