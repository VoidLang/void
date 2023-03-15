#include "Common.hpp"
#include "Launcher.hpp"
#include "util/Exceptions.hpp"

using namespace Void;

/**
 * Hey there,
 *  Welcome to the Void.
 *  I am Ábel (aka AdvancedAntiSkid) the founder of Void.
 *  If you have any questions feel free to join my discord.
 *    https://discord.gg/HdgnHqqGAW
 *
 * What is Void?
 *  Void is a dynamic, stack-based c++ virtual machine and compiler that I started making
 *  for educational purposes. In my free time I always aim towards learning as much as possible,
 *  and once I thought how cool it would be to have my own programming language. Well here it is.
 * Why Void?
 *  Void's vision is to provide an easy, understandable programming language for both
 *	educational and production purposes.
 * How stable is Void?
 *  According to my testings Void should be pretty stable, but keep in mind that I consider myself
 *  as a c++ beginner, therefore I'm positive most parts of Void could be written in so much easier ways.
 *  If you have encountered any bug smake sure to report them on my discord.
 * Can I contribute?
 *  Sure. Just make sure to write clean code, follow the code scheme, and comment out everything.
 *
 * For further information, please visit https://github.com/VoidLang/Void
 *
 * Written at: 10/08/2021 07:39 (MM-dd-yyyy HH-mm)
 * Last updated at: 03/15/2023 07:39 (MM-dd-yyyy HH-mm)
 */

/**
 * Start the program.
 * This must be a separated method because of the __try __except thing.
 */
void start(int argc, char** argv) {
    setConsoleSync(false);
    Launcher().start(argc, argv);
}

/**
 * Program entry point.
 */
int main(int argc, char** argv) {
    
    // What the...?
    // Well, there should probably be a better way of doing this, 
    // but gotta catch those windows-level errors...
    __try {
        start(argc, argv);
    }
    __except (Exceptions::handle(GetExceptionCode(), GetExceptionInformation())) {
        // no need to do anything in here because the exception is handled in Exceptions::handle
    }
    return 0;
}
