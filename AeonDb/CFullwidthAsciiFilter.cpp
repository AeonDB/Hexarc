//	CFullwidthAsciiFilter.cpp
//
//	CFullwidthAsciiFilter class
//
//	A concrete implementation of IPreprocess. This preprocessing technique changes
//	all ASCII fullwidth characters to their halfwidth character equivalents allowing
//	easier indexing and searching. This does not change non-ASCII characters such as
//	katakana.
//
//	http://unicode.org/charts/PDF/U0000.pdf
//	http://unicode.org/charts/PDF/UFF00.pdf
//
//	The following conversions are made (numbers are in hexidecimal Unicode):
//
//	Character	ASCII	Fullwidth
//	(Space)		0020	3000
//	!			0021	FF01
//	"			0022	FF02
//	#			0023	FF03
//	$			0024	FF04
//	%			0025	FF05
//	&			0026	FF06
//	'			0027	FF07
//	(			0028	FF08
//	)			0029	FF09
//	*			002A	FF0A
//	+			002B	FF0B
//	,			002C	FF0C
//	-			002D	FF0D
//	.			002E	FF0E
//	/			002F	FF0F
//	0			0030	FF10
//	1			0031	FF11
//	2			0032	FF12
//	3			0033	FF13
//	4			0034	FF14
//	5			0035	FF15
//	6			0036	FF16
//	7			0037	FF17
//	8			0038	FF18
//	9			0039	FF19
//	:			003A	FF1A
//	;			003B	FF1B
//	<			003C	FF1C
//	=			003D	FF1D
//	>			003E	FF1E
//	?			003F	FF1F
//	@			0040	FF20
//	A			0041	FF21
//	B			0042	FF22
//	C			0043	FF23
//	D			0044	FF24
//	E			0045	FF25
//	F			0046	FF26
//	G			0047	FF27
//	H			0048	FF28
//	I			0049	FF29
//	J			004A	FF2A
//	K			004B	FF2B
//	L			004C	FF2C
//	M			004D	FF2D
//	N			004E	FF2E
//	O			004F	FF2F
//	P			0050	FF30
//	Q			0051	FF31
//	R			0052	FF32
//	S			0053	FF33
//	T			0054	FF34
//	U			0055	FF35
//	V			0056	FF36
//	W			0057	FF37
//	X			0058	FF38
//	Y			0059	FF39
//	Z			005A	FF3A
//	[			005B	FF3B
//	/			005C	FF3C
//	]			005D	FF3D
//	^			005E	FF3E
//	_			005F	FF3F
//	`			0060	FF40
//	a			0061	FF41
//	b			0062	FF42
//	c			0063	FF43
//	d			0064	FF44
//	e			0065	FF45
//	f			0066	FF46
//	g			0067	FF47
//	h			0068	FF48
//	i			0069	FF49
//	j			006A	FF4A
//	k			006B	FF4B
//	l			006C	FF4C
//	m			006D	FF4D
//	n			006E	FF4E
//	o			006F	FF4F
//	p			0070	FF50
//	q			0071	FF51
//	r			0072	FF52
//	s			0073	FF53
//	t			0074	FF54
//	u			0075	FF55
//	v			0076	FF56
//	w			0077	FF57
//	x			0078	FF58
//	y			0079	FF59
//	z			007A	FF5A
//	{			007B	FF5B
//	|			007C	FF5C
//	}			007D	FF5D
//	~			007E	FF5E

#include "stdafx.h"

CFullwidthAsciiFilter::CFullwidthAsciiFilter (void)

//	CFullwidthAsciiFilter constructor

	{

	//	Intentionally blank.

	}

CFullwidthAsciiFilter::CFullwidthAsciiFilter (const CFullwidthAsciiFilter &Other)

//	CFullwidthAsciiFilter copy constructor

	{

	//	Intentionally blank.

	}

CFullwidthAsciiFilter::~CFullwidthAsciiFilter (void)

//	CFullwidthAsciiFilter destructor

	{

	//	Intentionally blank.

	}

CFullwidthAsciiFilter &CFullwidthAsciiFilter::operator= (const CFullwidthAsciiFilter &Other)

//	CFullwidthAsciiFilter copy assignment operator

	{
	return *this;
	}

IPreprocess *CFullwidthAsciiFilter::Clone (void)

//	Clone
//
//	Polymorphic method to decouple abstraction from implementation.

	{
	return new CFullwidthAsciiFilter();
	}

void CFullwidthAsciiFilter::Operation (CString &sData)

//	Operation
//
//	Decorator method for preprocessing text. This converts all fullwidth versions of ASCII to normal ASCII.

	{

	//	Iterate through each character in the string.
	//	If the character is fullwidth, change it to halfwidth.
	//	U+3000 is changed to U+0020.
	//	If the Unicode character is between U+FF01 to U+FF5E, subtract FEE0 to changed it to U+0021 to U+007E.

	}
