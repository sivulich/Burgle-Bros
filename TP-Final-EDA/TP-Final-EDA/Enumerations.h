#include <boost/preprocessor.hpp>
#include <iostream>

//******************************************************************************************************************************//
//										ENUMERATION WITH (SRTING <--> VALUE) CONVERTION											//
//	USAGE:																														//
//			#include "Enumeration.h"																							//
//			#include <iostream>																									//
//																																//
//			DEFINE_ENUM_WITH_CONVERSIONS(test1, (A)(B)(C))																		//
//			DEFINE_ENUM_WITH_CONVERSIONS(test2, (D,3)(E)(F))																	//
//			DEFINE_ENUM_WITH_CONVERSIONS(test3, (G,5)(H,7)(I,9))																//
//																																//
//			int main()																											//
//			{																													//
//				std::cout << toString(A) << " "<< toString((test1)1) << " " << toString((test1)5) << " " << std::endl;			//
//				std::cout << toEnum<test1>("A") << " " << toEnum<test1>("B") << " " << toEnum<test1>("D") << std::endl;			//
//																																//
//				std::cout << toString(D) << " "<< toString(E) << " " << toString(F) << " " << std::endl;						//
//				std::cout << toEnum<test2>("C") << " " << toEnum<test2>("E") << " " << toEnum<test2>("F") << std::endl;			//
//																																//
//				std::cout << toString(G) << " "<< toString(H) << " " << toString(I) << " " << std::endl;						//
//				std::cout << toEnum<test3>("G") << " " << toEnum<test3>("H") << " " << toEnum<test3>("I") << std::endl;			//
//				while (1);																										//
//			}																													//
//******************************************************************************************************************************//



// Auxiliar macro to form the switch cases in toString function
#define X_DEFINE_ENUM_WITH_CONVERSIONS_TOSTRING_CASE(r, data, elem)					\
	case elem : return BOOST_PP_STRINGIZE(elem);

// Auxiliar macro to compare the given string to each elemen int enum in template function toEnum
#define X_DEFINE_ENUM_WITH_CONVERSIONS_TOENUM(r,string, elem)						\
	if(!strcmp(string,BOOST_PP_STRINGIZE(elem))) return elem;

// Auxiliar macro to expand enumeration and check if default value has been set
//
// Left parenthesis (
// *element in the enum*
//  if the element has a value set..
//  =(name of the enum)value *cast it and asign it*
//  else nothing
//
// Right parenthesis )

#define ASIGN_NUMBER_TO_ELEMENT(r, data, elem)										\
	BOOST_PP_LPAREN()																\
	BOOST_PP_TUPLE_ELEM(0, elem)													\
	BOOST_PP_EXPR_IF(																\
					BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(elem), 2),					\
						= BOOST_PP_LPAREN() data BOOST_PP_RPAREN()					\
						BOOST_PP_TUPLE_ELEM(1, elem)								\
					)																\
	BOOST_PP_RPAREN()

////////////////////////////// MACRO ITSELF AND FUNCTION DEFINITIONS /////////////////////////////
#define DEFINE_ENUM_WITH_CONVERSIONS(name, enumerators)								\
	enum name {																		\
			BOOST_PP_SEQ_ENUM(														\
								BOOST_PP_SEQ_FOR_EACH(								\
									ASIGN_NUMBER_TO_ELEMENT,						\
									name,											\
									BOOST_PP_VARIADIC_SEQ_TO_SEQ(enumerators))) 	\
	};                                                                        		\
																			  		\
	inline const char* toString(name v)                                      		\
	{                                                                         		\
		switch (v)                                                            		\
		{                                                                     		\
			BOOST_PP_SEQ_FOR_EACH(                                            		\
				X_DEFINE_ENUM_WITH_CONVERSIONS_TOSTRING_CASE,          				\
				name,                                                         		\
				enumerators                                                   		\
			)                                                                 		\
			default: return "[Unknown " BOOST_PP_STRINGIZE(name) "]";         		\
		}                                                                     		\
	}																		  		\
																			  		\
	inline const name toEnum_##name(char * v)              							\
	{          																		\
		BOOST_PP_SEQ_FOR_EACH(												  		\
			X_DEFINE_ENUM_WITH_CONVERSIONS_TOENUM,					  				\
			v,															      		\
			enumerators														  		\
			)                                                                 		\
		std::cout<<"["<<v<<" is not in "<<BOOST_PP_STRINGIZE(name)"]"<<std::endl;	\
		return (name)4096;														  	\
	}