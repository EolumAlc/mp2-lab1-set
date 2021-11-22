
#include <gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*
#include "tbitfield.h"

using namespace std;

int main(){

    const int firstSze = 4, secondSize = 33;
    TBitField firstBf(firstSze), negFirstBf(firstSze), secondBf(secondSize), testBf(secondSize);

    testBf.SetBit(3);

    cout << testBf;
    cin >> testBf;
    cout << testBf;
    return 0;
}
*/
