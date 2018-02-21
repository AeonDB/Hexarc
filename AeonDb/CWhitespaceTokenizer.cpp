//	CWhitespaceTokenizer.cpp
//
//	CWhitespaceTokenizer class
//
//	A concrete implementation of the interface ITokenizer. This tokenizer uses
//	contiguous whitespace as the delimiter. It appends the substring and its position
//	into the CTermOccurenceStream class.
//
//	This class only considers whitespace in the ASCII range, 0-127.
//
//	Whitespace characters:
//	Name			Unicode Number (Hexadecimal)
//	Character Tab	0009
//	Line Feed		000A
//	Line Tab		000B
//	Form Feed		000C
//	Carriage Return	000D
//	Space			0020

#include "stdafx.h"

CWhitespaceTokenizer::CWhitespaceTokenizer (void)

//	CWhitespaceTokenizer constructor

	{

	//	Intentionally blank.

	}

CWhitespaceTokenizer::CWhitespaceTokenizer (const CWhitespaceTokenizer &Other)

//	CWhitespaceTokenizer copy constructor

	{

	//	Intentionally blank.

	}

CWhitespaceTokenizer::~CWhitespaceTokenizer ()

//	CWhitespaceTokenizer destructor

	{

	//	Intentionally blank.

	}

CWhitespaceTokenizer &CWhitespaceTokenizer::operator= (const CWhitespaceTokenizer &Other)

//	CWhitespaceTokenizer copy assignment operator

	{
	return *this;
	}

ITokenizer *CWhitespaceTokenizer::Clone (void)

//	Clone
//
//	Polymorphic method to decouple abstraction from implementation.

	{
	return new CWhitespaceTokenizer();
	}

CTermOccurenceStream CWhitespaceTokenizer::Operation (CString &sData)

//	Operation
//
//	Uses contiguous whitespace as a delimiter to produce substrings and store their positions.

	{
	CTermOccurenceStream Occurences;

	//	Iterate through the each character in the string.
	//	If the character is not a whitespace character such as tab, form feed, carriage return, etc, it is the beginning of a term.
		//	Save the character's position
	//	Continue iterating until the next whitespace character.
		//	Save the position of the previous character. It is the end of the term.
	//	Extract the substring using the beginning and end positions. Save the initial position of the term.
	//	Append the string and position to CTermOccurenceStream.

	return Occurences;
	}
