//	CPunctuationFilter.cpp
//
//	CPunctuationFilter class
//
//	A concrete implementation of IPreprocess. This preprocessing technique changes
//	unnecessary ASCII punctuation to space characters allowing easier tokenization.
//
//	The following characters are changed into space characters:
//	`	~	!	#	$	%	^	&	*	(	)	-	+	=	{	}
//	[	]	|	\	;	:	'	"	,	.	<	>	/	?

#include "stdafx.h"

CPunctuationFilter::CPunctuationFilter (void)

//	CPunctuationFilter constructor

	{

	//	Intentionally blank.

	}

CPunctuationFilter::CPunctuationFilter (const CPunctuationFilter &Other)

//	CPunctuationFilter copy constructor

	{

	//	Intentionally blank.

	}

CPunctuationFilter::~CPunctuationFilter (void)

//	CPunctuationFilter destructor

	{

	//	Intentionally blank.

	}

CPunctuationFilter &CPunctuationFilter::operator= (const CPunctuationFilter &Other)

//	CPunctuationFilter copy assignment operator

	{
	return *this;
	}

IPreprocess* CPunctuationFilter::Clone (void)

//	Clone
//
//	Polymorphic method to decouple abstraction from implementation.

	{
	return new CPunctuationFilter();
	}

void CPunctuationFilter::Operation (CString &sData)

//	Operation
//
//	Decorator method for preprocessing text. This converts unnecessary punctuation
//	into space characters without modifying positions of the words.

	{

	//	Iterate through each character in the string.

	//	If the character is one of the following change them into a space character:
	//	`	~	!	#	$	%	^	&	*	(	)	-	+	=	{	}	[	]	|	\	;	:	"	,	<	>	/	?

	//	If the character is a single quote character
		//	If there is a whitespace character preceding it or following it
			//	Change it to a space character.
		//	If it is the very beginning or end of the string
			//	Change it to a space character.

	//	If the character is a period
		//	If the period follows a whitespace character
			//	Change it into a space character
		//	While the character after it is not a space or not end of the string
			//	Swap the characters
			//	Change the period into a space character

	}
