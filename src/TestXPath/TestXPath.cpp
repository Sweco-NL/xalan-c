/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2001 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

#include <Include/PlatformDefinitions.hpp>



#include <cstdio>
#include <ctime>
#include <vector>



#if defined(XALAN_OLD_STREAM_HEADERS)
#include <iostream.h>
#else
#include <iostream>
#endif



#if !defined(NDEBUG) && defined(_MSC_VER)
#include <crtdbg.h>
#endif



#include <framework/URLInputSource.hpp>
#include <util/PlatformUtils.hpp>



#include <XalanDOM/XalanNode.hpp>
#include <XalanDOM/XalanDocument.hpp>
#include <XalanDOM/XalanElement.hpp>
#include <XalanDOM/XalanNodeList.hpp>



#include <PlatformSupport/DoubleSupport.hpp>
#include <PlatformSupport/DirectoryEnumerator.hpp>
#include <PlatformSupport/DOMStringHelper.hpp>
#include <PlatformSupport/XalanUnicode.hpp>
#include <PlatformSupport/XalanOutputStreamPrintWriter.hpp>
#include <PlatformSupport/XalanStdOutputStream.hpp>



#include <XPath/ElementPrefixResolverProxy.hpp>
#include <XPath/XPathInit.hpp>
#include <XPath/XObjectFactoryDefault.hpp>
#include <XPath/XPathEnvSupportDefault.hpp>
#include <XPath/XPathExecutionContextDefault.hpp>
#include <XPath/XPath.hpp>
#include <XPath/XPathProcessorImpl.hpp>
#include <XPath/XPathFactoryDefault.hpp>



#include <XMLSupport/FormatterTreeWalker.hpp>
#include <XMLSupport/FormatterToXML.hpp>
#include <XMLSupport/XMLSupportInit.hpp>



#include <XalanSourceTree/XalanSourceTreeDOMSupport.hpp>
#include <XalanSourceTree/XalanSourceTreeParserLiaison.hpp>



#include "NodeNameTreeWalker.hpp"



const XObjectPtr
ExecuteXPath(
			XPathProcessor&			theXPathProcessor,
			XPath&					theXPath,
			const XalanDOMString&	theXPathString,
			XalanNode* 				theContextNode,
			const PrefixResolver&	thePrefixResolver,
			const NodeRefListBase& 	theContextNodeList,
			XPathExecutionContext&	theExecutionContext)
{
	theXPathProcessor.initXPath(theXPath,
								theXPathString,
								thePrefixResolver);

	const XObjectPtr theResult =
		theXPath.execute(theContextNode, thePrefixResolver, theContextNodeList, theExecutionContext);

	return theResult;
}



bool
TestNumericResult(
			XPathProcessor&			theXPathProcessor,
			XPath&					theXPath,
			const XalanDOMString&	theXPathString,
			PrintWriter&			thePrintWriter,
			double					theExpectedResult,
			XalanNode* 				theContextNode,
			const PrefixResolver&	thePrefixResolver,
			const NodeRefListBase& 	theContextNodeList,
			XPathExecutionContext&	theExecutionContext)
{
	bool	fError = false;

	const XObjectPtr theResult =
		ExecuteXPath(theXPathProcessor,
					 theXPath,
					 theXPathString,
					 theContextNode,
					 thePrefixResolver,
					 theContextNodeList,
					 theExecutionContext);

	thePrintWriter.print(XALAN_STATIC_UCODE_STRING("Execution of XPath "));
	thePrintWriter.print(theXPathString);

	if (theResult->num() == theExpectedResult)
	{
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" succeeded."));
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The result was "));
		thePrintWriter.println(theResult->num());
	}
	else
	{
		fError = true;

		thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" failed!"));
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The expected result was "));
		thePrintWriter.println(theExpectedResult);
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The actual result was "));
		thePrintWriter.println(theResult->num());
	}

	return fError;
}



bool
TestStringResult(
			XPathProcessor&			theXPathProcessor,
			XPath&					theXPath,
			const XalanDOMString&	theXPathString,
			PrintWriter&			thePrintWriter,
			const XalanDOMString&	theExpectedResult,
			XalanNode* 				theContextNode,
			const PrefixResolver&	thePrefixResolver,
			const NodeRefListBase& 	theContextNodeList,
			XPathExecutionContext&	theExecutionContext)
{
	bool	fError = false;

	const XObjectPtr theResult =
		ExecuteXPath(theXPathProcessor,
					 theXPath,
					 theXPathString,
					 theContextNode,
					 thePrefixResolver,
					 theContextNodeList,
					 theExecutionContext);

	thePrintWriter.print(XALAN_STATIC_UCODE_STRING("Execution of XPath "));
	thePrintWriter.print(theXPathString);

	if (equals(theResult->str(), theExpectedResult) == true)
	{
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" succeeded."));
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The result was \""));
		thePrintWriter.print(theResult->str());
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
	}
	else
	{
		fError = true;

		thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" failed!"));
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The expected result was \""));
		thePrintWriter.print(theExpectedResult);
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The actual result was \""));
		thePrintWriter.print(theResult->str());
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
	}

	return fError;
}



bool
TestBooleanResult(
			XPathProcessor&			theXPathProcessor,
			XPath&					theXPath,
			const XalanDOMString&		theXPathString,
			PrintWriter&			thePrintWriter,
			bool					theExpectedResult,
			XalanNode* 		theContextNode,
			const PrefixResolver&	thePrefixResolver,
			const NodeRefListBase& 	theContextNodeList,
			XPathExecutionContext&	theExecutionContext)
{
	bool	fError = false;

	const XObjectPtr theResult =
		ExecuteXPath(theXPathProcessor,
					 theXPath,
					 theXPathString,
					 theContextNode,
					 thePrefixResolver,
					 theContextNodeList,
					 theExecutionContext);

	bool	fDump = false;

	if (fDump == true)
	{
		thePrintWriter.println();
		thePrintWriter.println();
		theXPath.getExpression().dumpOpCodeMap(thePrintWriter);
		thePrintWriter.println();
		theXPath.getExpression().dumpTokenQueue(thePrintWriter);
		thePrintWriter.println();
		thePrintWriter.println();
	}

	thePrintWriter.print(XALAN_STATIC_UCODE_STRING("Execution of XPath "));
	thePrintWriter.print(theXPathString);

	if (theResult->boolean() == theExpectedResult)
	{
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" succeeded."));
		thePrintWriter.print(("The result was "));
		thePrintWriter.print(theResult->boolean());
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING("."));
	}
	else
	{
		fError = true;

		thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" failed!"));
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The expected result was \""));
		thePrintWriter.print(theExpectedResult);
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("The actual result was \""));
		thePrintWriter.print(theResult->boolean());
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
	}

	return fError;
}



XalanDocument*
ParseXML(
			XMLParserLiaison&		theLiaison,
			const XalanDOMString&	theFileName)
{
	const URLInputSource	theURLInputSource(c_wstr(theFileName));

	return theLiaison.parseXMLStream(theURLInputSource);
}



XalanDOMString
GetAttributeFromNode(
			XalanNode*				theNode,
			const XalanDOMString&	theAttributeName)
{
	XalanDOMString	theResult;

	if (theNode->getNodeType() == XalanNode::ELEMENT_NODE)
	{
		const XalanElement*	const	theElement =
#if defined(XALAN_OLD_STYLE_CASTS)
					(const XalanElement*)theNode;
#else
					static_cast<const XalanElement*>(theNode);
#endif

		theResult = theElement->getAttribute(theAttributeName);
	}

	return theResult;
}



XalanDOMString
FindNodeAndGetAttributeValue(
			XalanNode*				theStartNode,
			const XalanDOMString&	theNodeName,
			const XalanDOMString&	theAttributeName)
{
	XalanDOMString			theResult;

	NodeNameTreeWalker	theTreeWalker;

	theTreeWalker.findMatchingNodes(theNodeName,
									theStartNode);

	const NodeNameTreeWalker::NodeVectorType&	theMatchingNodes =
			theTreeWalker.getMatchingNodes();

	if (theMatchingNodes.size() == 1)
	{
		XalanNode* const	theMatchingNode = theMatchingNodes[0];

		if (theMatchingNode != 0)
		{
			theResult = GetAttributeFromNode(theMatchingNode,
											 theAttributeName);
		}
	}

	return theResult;
}



bool
GetXSLInput(
			XMLParserLiaison&		theLiaison,
			const XalanDOMString&	theXSLFileURL,
			XalanDOMString&			theContextNodeMatchPattern,
			XalanDOMString&			theXPathString)
{
	bool					fResult = false;

	XalanDocument* const	theDocument =
		ParseXML(theLiaison,
				 theXSLFileURL);

	if (theDocument != 0)
	{
		const XalanDOMString	theContextNodeName(XALAN_STATIC_UCODE_STRING("xsl:for-each"));
		const XalanDOMString	theAttributeName(XALAN_STATIC_UCODE_STRING("select"));

		theContextNodeMatchPattern =
			 FindNodeAndGetAttributeValue(theDocument->getDocumentElement(),
										  theContextNodeName,
										  theAttributeName);

		if (length(theContextNodeMatchPattern) != 0)
		{
			const XalanDOMString	theSelectNodeName(XALAN_STATIC_UCODE_STRING("xsl:apply-templates"));

			theXPathString =
				 FindNodeAndGetAttributeValue(theDocument->getDocumentElement(),
											  theSelectNodeName,
											  theAttributeName);
			if (length(theXPathString) != 0)
			{
				fResult = true;
			}
		}
	}

	return fResult;
}



XalanNode*
FindContextNode(
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			XPathFactory&			theXPathFactory,
			XalanDocument*			theDocument,
			const XalanDOMString&	theContextNodeMatchPattern,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	XalanNode*		theResult = 0;

	XPath* const	theXPath = theXPathFactory.create();

	XPathGuard		theGuard(
						theXPathFactory,
						theXPath);

	XalanElement*				theNamespaceContext = 0;
	ElementPrefixResolverProxy	thePrefixResolver(theNamespaceContext, theXPathEnvSupport, theDOMSupport);
	NodeRefList					theContextNodeList;

	const XObjectPtr	theXObject =
		ExecuteXPath(theXPathProcessor,
					 *theXPath,
					 theContextNodeMatchPattern,
					 theDocument,
					 thePrefixResolver,
					 theContextNodeList,
					 theExecutionContext);

	try
	{
		assert(theXObject.null() == false);

		const NodeRefListBase&	theResultList =
						theXObject->nodeset();

		if (theResultList.getLength() == 0)
		{
			thePrintWriter.print(XALAN_STATIC_UCODE_STRING("FindContextNode: Unable to find context node using select \""));
			thePrintWriter.print(theContextNodeMatchPattern);
			thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
			thePrintWriter.println(XALAN_STATIC_UCODE_STRING("FindContextNode: No nodes matched the pattern."));
		}
		else if (theResultList.getLength() != 1)
		{
			thePrintWriter.print(XALAN_STATIC_UCODE_STRING("FindContextNode: Unable to find context node using select \""));
			thePrintWriter.print(theContextNodeMatchPattern);
			thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
			thePrintWriter.println(XALAN_STATIC_UCODE_STRING("FindContextNode: More than one node matched the pattern."));
		}
		else
		{
			theResult = theResultList.item(0);
		}
	}
	catch(...)
	{
		thePrintWriter.print(XALAN_STATIC_UCODE_STRING("FindContextNode: Error executing match pattern \""));
		thePrintWriter.print(theContextNodeMatchPattern);
		thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\"."));
	}

	return theResult;
}



bool
TestAxisResult(
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			XMLParserLiaison&		theLiaison,
			XPathFactory&			theXPathFactory,
			const XalanDOMString&	theXMLFileURL,
			const XalanDOMString&	theXSLFileURL,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	bool					fError = false;

	XalanDocument* const	theXMLDocument = ParseXML(theLiaison,
													  theXMLFileURL);

	if (theXMLDocument != 0)
	{
		XalanDOMString		theContextNodeMatchPattern;
		XalanDOMString		theXPathString;

		if (GetXSLInput(theLiaison,
						theXSLFileURL,
						theContextNodeMatchPattern,
						theXPathString) == true)
		{
			XalanNode* const	theContextNode =
				FindContextNode(theXPathProcessor,
								theXPathEnvSupport,
								theDOMSupport,
								theXPathFactory,
								theXMLDocument,
								theContextNodeMatchPattern,
								thePrintWriter,
								theExecutionContext);

			if (theContextNode != 0)
			{
				XalanElement* const				theNamespaceContext = 0;
				ElementPrefixResolverProxy		thePrefixResolver(theNamespaceContext, theXPathEnvSupport, theDOMSupport);
				NodeRefList						theContextNodeList;

				XPath* const	theXPath = theXPathFactory.create();

				XPathGuard		theGuard(theXPathFactory,
										 theXPath);

				theXPathProcessor.initXPath(*theXPath,
											theXPathString,
											thePrefixResolver);

				bool	fDump = false;

				if (fDump == true)
				{
					thePrintWriter.println();
					thePrintWriter.println();
					theXPath->getExpression().dumpOpCodeMap(thePrintWriter);
					thePrintWriter.println();
					theXPath->getExpression().dumpTokenQueue(thePrintWriter);
					thePrintWriter.println();
					thePrintWriter.println();
				}

				const XObjectPtr theResult =
					theXPath->execute(theContextNode, thePrefixResolver, theContextNodeList, theExecutionContext);

				try
				{
					assert(theResult.null() == false);

					const NodeRefListBase&	theResultList =
						theResult->nodeset();

					const unsigned int	theLength = theResultList.getLength();

					if (theLength == 0)
					{
						thePrintWriter.println(XALAN_STATIC_UCODE_STRING("<out/>"));
					}
					else
					{
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("<out>"));

						for (unsigned int i = 0; i < theLength; i++)
						{
							thePrintWriter.print(theResultList.item(i)->getNodeName());
							thePrintWriter.print(XALAN_STATIC_UCODE_STRING(" "));
						}

						thePrintWriter.println(XALAN_STATIC_UCODE_STRING("</out>"));
					}
				}
				catch(...)
				{
					thePrintWriter.print(XALAN_STATIC_UCODE_STRING("Execution of XPath "));
					thePrintWriter.print(theXPathString);
					thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" failed!"));
				}
			}
		}
	}

	theLiaison.reset();

	return fError;
}



bool
TestPredicateResult(
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			XMLParserLiaison&		theLiaison,
			XPathFactory&			theXPathFactory,
			const XalanDOMString&	theXMLFileURL,
			const XalanDOMString&	theXSLFileURL,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	bool					fError = false;

	XalanDocument* const	theXMLDocument =
				ParseXML(theLiaison,
						 theXMLFileURL);

	if (theXMLDocument != 0)
	{
		XalanDOMString		theContextNodeMatchPattern;
		XalanDOMString		theXPathString;

		if (GetXSLInput(theLiaison,
						theXSLFileURL,
						theContextNodeMatchPattern,
						theXPathString) == true)
		{
			XalanNode* const	theContextNode =
				FindContextNode(theXPathProcessor,
								theXPathEnvSupport,
								theDOMSupport,
								theXPathFactory,
								theXMLDocument,
								theContextNodeMatchPattern,
								thePrintWriter,
								theExecutionContext);

			if (theContextNode != 0)
			{
				XalanElement* const				theNamespaceContext = 0;
				ElementPrefixResolverProxy		thePrefixResolver(theNamespaceContext, theXPathEnvSupport, theDOMSupport);
				NodeRefList						theContextNodeList;

				XPath* const	theXPath1 = theXPathFactory.create();

				XPathGuard	theGuard1(theXPathFactory,
									  theXPath1);

				theXPathProcessor.initXPath(*theXPath1,
											TranscodeFromLocalCodePage("following-sibling::*"),
											thePrefixResolver);

				XPath* const	theXPath2 = theXPathFactory.create();

				XPathGuard	theGuard2(theXPathFactory,
									  theXPath2);

				theXPathProcessor.initXPath(*theXPath2,
											TranscodeFromLocalCodePage("descendant::*"),
											thePrefixResolver);

				bool	fDump = false;

				if (fDump == true)
				{
					thePrintWriter.println();
					thePrintWriter.println();
					theXPath1->getExpression().dumpOpCodeMap(thePrintWriter);
					thePrintWriter.println();
					theXPath1->getExpression().dumpTokenQueue(thePrintWriter);
					thePrintWriter.println();
					thePrintWriter.println();
					theXPath2->getExpression().dumpOpCodeMap(thePrintWriter);
					thePrintWriter.println();
					theXPath2->getExpression().dumpTokenQueue(thePrintWriter);
					thePrintWriter.println();
					thePrintWriter.println();
				}

				XalanNode*	theContextNode = theXMLDocument->getFirstChild()->getFirstChild();

				for( ; theContextNode != 0; theContextNode = theContextNode->getNextSibling())
				{
					if (theContextNode->getNodeType() != XalanNode::ELEMENT_NODE)
					{
						continue;
					}

					const XObjectPtr theResult1 =
							theXPath1->execute(theExecutionContext);

					try
					{
						assert(theResult1.null() == false);

						const NodeRefListBase&	theResultList =
								theResult1->nodeset();

						const unsigned int	theLength = theResultList.getLength();

						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("theResult1->str() == \""));
						thePrintWriter.print(theResult1->str());
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("\""));
						thePrintWriter.println();

						if (theLength > 0)
						{
							for (unsigned int i = 0; i < theLength; i++)
							{
								thePrintWriter.print(theResultList.item(i)->getNodeName());
								thePrintWriter.println();
							}
						}
					}
					catch(...)
					{
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("Execution of XPath "));
						thePrintWriter.print(theXPathString);
						thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" failed!"));
					}

					const XObjectPtr 	theResult2 =
							theXPath2->execute(theExecutionContext);

					try
					{
						assert(theResult2.null() == false);

						const NodeRefListBase&	theResultList =
								theResult2->nodeset();

						const int	theLength = theResultList.getLength();

						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("theResult2->str() == \""));
						thePrintWriter.print(theResult2->str());
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("\""));
						thePrintWriter.println();

						if (theLength > 0)
						{
							for (int i = 0; i < theLength; i++)
							{
								thePrintWriter.print(theResultList.item(i)->getNodeName());
								thePrintWriter.println();
							}
						}
					}
					catch(...)
					{
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("Execution of XPath "));
						thePrintWriter.print(theXPathString);
						thePrintWriter.println(XALAN_STATIC_UCODE_STRING(" failed!"));
					}

					if (theResult1->equals(*theResult2, theExecutionContext) == true)
					{
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("theResult1 is equal to theResult2"));
						thePrintWriter.println();
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("theContextNode->getNodeName() == \""));
						thePrintWriter.print(theContextNode->getNodeName());
						thePrintWriter.print(XALAN_STATIC_UCODE_STRING("\"  theContextNode->getNodeValue() == \""));
						thePrintWriter.print(theContextNode->getNodeValue());
						thePrintWriter.println(XALAN_STATIC_UCODE_STRING("\""));
					}
				}
			}
		}
	}

	return fError;
}



const char* const	theNumericTestInput[] =
{
	"9 + 7 - 6 * 42 + 36 div 3 + 100 - 2 * 6",
	"9 + 7 - 6 + 3 + 24 - 32 - 89 + 123 - 12256 + 89957",
	"0 + 0",
	"1 div 2",
	"1 * 0.25",
	"3 * 3 * 3",
	"9 div 3 div 3",
	"15.95 - 13.56",
	0
};



const double	theNumericTestExpectedOutput[] =
{
	-136.0,
	77740.0,
	0,
	0.5,
	0.25,
	27,
	1,
	15.95 - 13.56,
	0	// This is a dummy entry and should be last.
};



void
TestNumericResults(
			XPathFactory&			theXPathFactory,
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	assert(sizeof(theNumericTestInput) / sizeof(theNumericTestInput[0]) ==
			sizeof(theNumericTestExpectedOutput) / sizeof(theNumericTestExpectedOutput[0]));

	for(int i = 0; theNumericTestInput[i] != 0; i++)
	{
		try
		{
			XPath* const	theXPath = theXPathFactory.create();

			XPathGuard		theGuard(theXPathFactory,
									 theXPath);

			TestNumericResult(theXPathProcessor,
							  *theXPath,
							  TranscodeFromLocalCodePage(theNumericTestInput[i]),
							  thePrintWriter,
							  theNumericTestExpectedOutput[i],
							  0,
							  ElementPrefixResolverProxy(0, theXPathEnvSupport, theDOMSupport),
							  NodeRefList(),
							  theExecutionContext);
		}
		catch(...)
		{
			thePrintWriter.print("Exception caught evaluating XPath \"");
			thePrintWriter.print(theNumericTestInput[i]);
			thePrintWriter.println();
		}
	}
}



const char* const	theStringTestInput[] =
{
	"string(0)",
	"string(1.5)",
	"string(-1.5)",
	"string(0.5)",
	"string(-0.5)",
	"string(9)",
	"string(-9)",
	"string(\"9\")",
	"string(0.25)",

	"concat(\"foo\", \"bar\")",
	"concat(\"foo\", \"bar\", \"sky\")",

	"contains(\"foobar\", \"oba\")",
	"contains(\"LotusXSL4C is great\", \"boag\")",

	"starts-with(\"foobar\", \"foo\")",
	"starts-with(\"LotusXSL4C is great\", \"boag\")",

	"substring-after(\"1999/04/01\", \"/\")",
	"substring-after(\"1999/04/01\", \"19\")",

	"substring-before(\"1999/04/01\", \"/\")",
	"substring-before(\"1999/04/01\", \"01\")",

	"substring(\"12345\", 1.5, 2.6)",
	"substring(\"12345\", 0, 3)",
	"substring(\"12345\", 5, 29)",
	"substring(\"12345\", -1, 2)",
	"substring(\"12345\", -2, -1)",
	"substring(\"12345\", -2)",

	"normalize-space(\"   aa   a  \")",

	"translate(\"---aaa--\", \"abc-\", \"ABC\")",

	"5 = 0",
	"5 = 5",
	0
};


const char* const	theStringTestExpectedOutput[] =
{
	"0",
	"1.5",
	"-1.5",
	"0.5",
	"-0.5",
	"9",
	"-9",
	"9",
	"0.25",

	"foobar",
	"foobarsky",

	"true",
	"false",

	"true",
	"false",

	"04/01",
	"99/04/01",

	"1999",
	"1999/04/",

	"234",
	"12",
	"5",
	"",
	"",
	"12345",

	"aa a",

	"AAA",

	"false",
	"true",
	0
};



void
TestStringResults(
			XPathFactory&			theXPathFactory,
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	assert(sizeof(theStringTestInput) == sizeof(theStringTestExpectedOutput));

	for(int i = 0; theStringTestInput[i] != 0; i++)
	{
		try
		{
			XPath* const	theXPath = theXPathFactory.create();

			XPathGuard	theGuard(theXPathFactory,
								 theXPath);

			TestStringResult(theXPathProcessor,
							 *theXPath,
							 TranscodeFromLocalCodePage(theStringTestInput[i]),
							 thePrintWriter,
							 TranscodeFromLocalCodePage(theStringTestExpectedOutput[i]),
							 0,
							 ElementPrefixResolverProxy(0, theXPathEnvSupport, theDOMSupport),
							 NodeRefList(),
							 theExecutionContext);
		}
		catch(...)
		{
			thePrintWriter.print("Exception caught evaluating XPath \"");
			thePrintWriter.print(theStringTestInput[i]);
			thePrintWriter.println();
		}
	}
}



const char* const	theBooleanTestInput[] =
{
	"0 < 2 < 3",
	"0 < 2 > 3",
	"1 < 2 < 3",

	"0 div 0 != 0 div 0",
	"0 div 0 = 0 div 0",
	"1 < 0 div 0",
	"1 <= 0 div 0",
	"2 > 0 div 0",
	"2 >= 0 div 0",

	"1 < 2",
	"1500 < 657",
	"1465787676 < 5 div 0",
	"4657 div 0 < 4563745658",

	"1000 <= 256000",
	"1000 <= 1000",
	"200564 <= 1999",
	"5768594 <= 56 div 0",
	"564783 div 0 <= 6758494857",

	"2015 > 100",
	"56478 > 240000",
	"4657 div 0 > 57683946",
	"573068574 > 5 div 0",

	"46000 >= 1500",
	"56983 >= 56983",
	"460983 >= 1500000",
	"67594876 div 0 >= 576849",

	"1465787676 >= 5 div 0",
	"-1465787676 >= -5 div 0",
	"-1679 < -87 div 0",

	"1 = 2 = 0",
	"1 = 2 != 0",

	0
};



const bool	theBooleanTestExpectedOutput[] =
{
	true,
	false,
	true,

	true,
	false,
	false,
	false,
	false,
	false,

	true,
	false,
	true,
	false,

	true,
	true,
	false,
	true,
	false,

	true,
	false,
	true,
	false,

	true,
	true,
	false,
	true,

	false,
	true,
	false,

	true,
	false,

	0
};



void
TestBooleanResults(
			XPathFactory&			theXPathFactory,
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	assert(sizeof(theBooleanTestInput) / sizeof(theBooleanTestInput[0]) ==
				sizeof(theBooleanTestExpectedOutput) / sizeof(theBooleanTestExpectedOutput[0]));

	for(int i = 0; theBooleanTestInput[i] != 0; i++)
	{
		try
		{
			XPath* const	theXPath = theXPathFactory.create();

			XPathGuard	theGuard(theXPathFactory,
								 theXPath);

			TestBooleanResult(theXPathProcessor,
							  *theXPath,
							  TranscodeFromLocalCodePage(theBooleanTestInput[i]),
							  thePrintWriter,
							  theBooleanTestExpectedOutput[i],
							  0,
							  ElementPrefixResolverProxy(0, theXPathEnvSupport, theDOMSupport),
							  NodeRefList(),
							  theExecutionContext);
		}
		catch(...)
		{
			thePrintWriter.print("Exception caught evaluating XPath \"");
			thePrintWriter.print(theStringTestInput[i]);
			thePrintWriter.println();
		}
	}
}



XalanDOMString
GetXSLFileName(const XalanDOMString&		theXMLFileName)
{
	XalanDOMString	theResult;

	int			thePeriodIndex = -1;

	const int	theLength = length(theXMLFileName);

	for (int i = theLength - 1; i > 0; i--)
	{
		if (charAt(theXMLFileName, i) == XalanUnicode::charFullStop)
		{
			thePeriodIndex = i;

			break;
		}
	}

	if (thePeriodIndex != -1)
	{
		theResult = substring(theXMLFileName,
							  0,
							  thePeriodIndex + 1);

		theResult += XALAN_STATIC_UCODE_STRING("xsl");
	}

	return theResult;
}



void
TestAxes(
			XPathFactory&			theXPathFactory,
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			XMLParserLiaison&		theLiaison,
			const XalanDOMString&	theDirectory,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	const XalanDOMString	theProtocol(XALAN_STATIC_UCODE_STRING("file://"));
	const XalanDOMString	theBaseURL = theProtocol + theDirectory;
#if defined(WIN32)
	const XalanDOMString	theSearchSpecification(theDirectory + "\\*");
#else
	const XalanDOMString	theSearchSpecification(theDirectory + "/*");
#endif
	const XalanDOMString	theXMLSuffix(XALAN_STATIC_UCODE_STRING(".xml"));

#if defined(XALAN_NO_NAMESPACES)
	typedef vector<XalanDOMString>		FileNameVectorType;
#else
	typedef std::vector<XalanDOMString>	FileNameVectorType;
#endif

	DirectoryEnumeratorFunctor<FileNameVectorType, XalanDOMString>	theEnumerator;

	FileNameVectorType	theFiles;

	theEnumerator(theSearchSpecification,
				  theFiles);

	thePrintWriter.println();

	for(FileNameVectorType::size_type	i = 0; i < theFiles.size(); i++)
	{
		if (endsWith(theFiles[i], theXMLSuffix) == true)
		{
			try
			{
				// Create a fully qualified URL specification...
				const XalanDOMString	theXMLFileName = theBaseURL + theFiles[i];

				// Get the name of the corresponding XSL file...
				const XalanDOMString	theXSLFileName = GetXSLFileName(theXMLFileName);

				XPathGuard	theXPath(theXPathFactory,
									 theXPathFactory.create());

				TestAxisResult(theXPathProcessor,
							   theXPathEnvSupport,
							   theDOMSupport,
							   theLiaison,
							   theXPathFactory,
							   theXMLFileName,
							   theXSLFileName,
							   thePrintWriter,
							   theExecutionContext);
			}
			catch(...)
			{
				thePrintWriter.print("Exception caught evaluating XPath!");
				thePrintWriter.println();
			}
		}
	}
}



void
RunTests(
			XPathFactory&			theXPathFactory,
			XPathProcessor&			theXPathProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			DOMSupport&				theDOMSupport,
			XMLParserLiaison&		theLiaison,
			PrintWriter&			thePrintWriter,
			XPathExecutionContext&	theExecutionContext)
{
	TestNumericResults(theXPathFactory,
					   theXPathProcessor,
					   theXPathEnvSupport,
					   theDOMSupport,
					   thePrintWriter,
					   theExecutionContext);

	TestStringResults(theXPathFactory,
					  theXPathProcessor,
					  theXPathEnvSupport,
					  theDOMSupport,
					  thePrintWriter,
					  theExecutionContext);

	TestBooleanResults(theXPathFactory,
					   theXPathProcessor,
					   theXPathEnvSupport,
					   theDOMSupport,
					   thePrintWriter,
					   theExecutionContext);

	TestAxes(theXPathFactory,
			 theXPathProcessor,
		     theXPathEnvSupport,
			 theDOMSupport,
			 theLiaison,
			 StaticStringToDOMString(XALAN_STATIC_UCODE_STRING("/xsl-test/conf/axes/")),
			 thePrintWriter,
		     theExecutionContext);
}



int
main(int			/* argc */,
	 const char*	/* argv */ [])
{
#if !defined (XALAN_NO_NAMESPACES)
	using std::cout;
#endif

#if !defined(NDEBUG) && defined(_MSC_VER)
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

   _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
#endif

	XMLPlatformUtils::Initialize();

	{
		XMLSupportInit					theXMLSupportInit;
		XPathInit						theXPathInit;

		XPathEnvSupportDefault			theXPathEnvSupport;
		XalanSourceTreeDOMSupport		theDOMSupport;
		XObjectFactoryDefault			theXObjectFactory;
		XPathFactoryDefault				theXPathFactory;
		XPathProcessorImpl				theXPathProcessor;

		XPathExecutionContextDefault	theExecutionContext(theXPathEnvSupport,
															theDOMSupport,
															theXObjectFactory);

		XalanStdOutputStream			theStdOut(cout);
		XalanOutputStreamPrintWriter	thePrintWriter(theStdOut);
		XalanSourceTreeParserLiaison	theLiaison(theDOMSupport);

		RunTests(theXPathFactory,
				 theXPathProcessor,
				 theXPathEnvSupport,
				 theDOMSupport,
				 theLiaison,
				 thePrintWriter,
				 theExecutionContext);
	}

	XMLPlatformUtils::Terminate();

	return 0;
}