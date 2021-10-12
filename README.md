# szsDemoPatch
A console based executable that patches .szs files into the "July Special Disc 2002" Super Mario Sunshine demo.

# **IMPORTANT/DISCLAIMER**:
**AS THIS PROGRAM DEALS WITH DATA MANIPULATION, IT IS RECOMMENED TO KEEP BACKUPS OF "zz_marioTaiken5.tgc" AND ANY ".szs" FILE YOU MAY USE WITH THE PROGRAM. WHILE THERE ARE MANY STEPS IN PLACE FOR "szsDemoPatch" TO ONLY MANIPULATE THE DATA OF "zz_marioTaiken5.tgc", IT IS THE SOLE RESPONSIBILITY OF THE USER IF AN UNINTENDED FILE OR FILES BECOMES CORRUPT AS A RESULT OF USING THIS PROGRAM! I(AngryMax), WILL NOT BE HELD RESPONSIBLE IF ANY SUCH CASE APPEARS.**

# **Build Instructions:**
Open szsDemoPatch.sln in Visual Studio 2019, then build with Solution Configuration set to "Release," and Solution Platform set to "x86." The Windows SDK Version used was "10.0," and the C++ Language Standard is "ISO C++ 14 Standard." I'm not good with build instructions, I hope that's enough/not too much information ¯\_(ツ)_/¯

# **Command Line Arguments:**
**Template:** "szsDemoPatch.exe" "zz_marioTaiken5.tgc" "szs" "patched level" "level name"

**"szsDemoPatch.exe"** - Path to szsDemoPatch.exe

**"zz_marioTaiken5.tgc"** - Path to "zz_MarioTaiken5.tgc"

**"szs"** - Path to the level you want to patch in(Ex: "C:\Path\sirena0.szs")

**"patched level"** - The demo level you are patching over. More about that below in the "Demo Level Arguments" section

**"level name"** - The level you want SMS to think is patched in. 99% of the time you'll probably just make this the name of the szs you're patching in(Ex: "sirena0.szs" It's important to always add ".szs" at the end)

# **Demo Level Arguments:**
**These are the arguments you can use for the "patched level" argument** 
"bianco0", "bianco0.szs", "b0" | "bianco1", "bianco1.szs", "b1" | "biancoBoss", "biancoBoss.szs", "bb" | "coro_ex1", "coro_ex1.szs", "ce1" | "mamma1", "mamma1.szs", "m1" |
"mamma2", "mamma2.szs", "m2" | "ricco0", "ricco0.szs", "r0" | "ricco8", "ricco8.szs", "r8"

If you want to paste an szs file over "option", then I reccomend you do it manually. A document detailing how to patch "zz_marioTaiken5.tgc" manually will be linked as soon as I make it

 Important note: If you enter an argument that doesn't exist, the program will just default to patched over bianco0.szs. Prob not good design lmao.
