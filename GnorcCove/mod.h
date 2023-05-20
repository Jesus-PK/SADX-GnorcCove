#pragma once

//	This extern is needed to declare HelperFunctions in other .cpp's that need their definition.
//	Write "HelperFunctions HelperFunctionsGlobal;" outside your extern C in mod.cpp and add this extern below of this mod.h
//	Now if you need the HelperFunctions definition, you only need to call this header to get them on the .cpp you need (or you can call this header in pch.h and you won't have to bother including it manually)

extern HelperFunctions HelperFunctionsGlobal;