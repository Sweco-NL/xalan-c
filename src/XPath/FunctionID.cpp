/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2000 The Apache Software Foundation.  All rights 
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
#include "FunctionID.hpp"



#include <DOMSupport/DOMServices.hpp>



#include "XObjectFactory.hpp"



FunctionID::FunctionID()
{
}



FunctionID::~FunctionID()
{
}



XObjectPtr
FunctionID::execute(
			XPathExecutionContext&	executionContext,
			XalanNode*				context)
{
	executionContext.error(getError(), context);

	return XObjectPtr(0);
}



XObjectPtr
FunctionID::execute(
		XPathExecutionContext&			executionContext,
		XalanNode*						context,			
		const XObjectPtr				arg1)
{
	assert(arg1.null() == false);	

	if (context == 0)
	{
		executionContext.error("The id() function requires a non-null context node!",
							   context);
	}	

	// Do the callback to get the data.
	FunctionIDXObjectTypeCallback	theCallback(executionContext);

	const XalanDOMString	theResultString =
		theCallback.processCallback(*arg1);

	// Get the context document, so we can search for nodes.
	const XalanDocument* const	theDocContext = context->getNodeType() == XalanNode::DOCUMENT_NODE ?
#if defined(XALAN_OLD_STYLE_CASTS)
									(const XalanDocument*)context :
#else
									static_cast<const XalanDocument*>(context) :
#endif
									context->getOwnerDocument();
	assert(theDocContext != 0);

	typedef XPathExecutionContext::BorrowReturnMutableNodeRefList	BorrowReturnMutableNodeRefList;

	// This list will hold the nodes we find.

	BorrowReturnMutableNodeRefList	theNodeList(executionContext);

	// If there is no context, we cannot continue.
	if(0 == theDocContext)
	{
		executionContext.error("The context node does not have an owner document!",
							   context);
    }
	else if (length(theResultString) > 0)
	{
#if defined(XALAN_NO_NAMESPACES)
		typedef set<XalanDOMString, less<XalanDOMString> >	TokenSetType;
#else
		typedef std::set<XalanDOMString>	TokenSetType;
#endif

		// This set will hold tokens that we've previously found, so
		// we can avoid looking more than once.
		TokenSetType		thePreviousTokens;

		StringTokenizer		theTokenizer(theResultString);

		typedef XPathExecutionContext::GetAndReleaseCachedString	GetAndReleaseCachedString;

		GetAndReleaseCachedString	theGuard(executionContext);

		XalanDOMString&				theToken = theGuard.get();

		// Parse the result string...
		while(theTokenizer.hasMoreTokens() == true)
		{
			theTokenizer.nextToken(theToken);

			if (length(theToken) > 0)
			{
				// See if we've already seen this one...
				TokenSetType::const_iterator	i =
					thePreviousTokens.find(theToken);

				if (i == thePreviousTokens.end())
				{
					thePreviousTokens.insert(theToken);

					XalanNode* const	theNode = theDocContext->getElementById(theToken);

					if (theNode != 0)
					{
						theNodeList->addNodeInDocOrder(theNode, executionContext);
					}
				}
			}
		}
	}

	return executionContext.getXObjectFactory().createNodeSet(theNodeList);
}



XObjectPtr
FunctionID::execute(
			XPathExecutionContext&	executionContext,
			XalanNode*				context,			
			const XObjectPtr		/* arg1 */,
			const XObjectPtr		/* arg2 */)
{
	executionContext.error(getError(), context);

	return XObjectPtr(0);
}



XObjectPtr
FunctionID::execute(
			XPathExecutionContext&	executionContext,
			XalanNode*				context,			
			const XObjectPtr		/* arg1 */,
			const XObjectPtr		/* arg2 */,
			const XObjectPtr		/* arg3 */)
{
	executionContext.error(getError(), context);

	return XObjectPtr(0);
}



XObjectPtr
FunctionID::execute(
			XPathExecutionContext&			executionContext,
			XalanNode*						context,
			int								/* opPos */,
			const XObjectArgVectorType&		/* args */)
{
	executionContext.error(getError(), context);

	return XObjectPtr(0);
}



#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
Function*
#else
FunctionID*
#endif
FunctionID::clone() const
{
	return new FunctionID(*this);
}



const XalanDOMString
FunctionID::getError() const
{
	return XALAN_STATIC_UCODE_STRING(
		"The id() function takes one argument!");
}



FunctionID::FunctionIDXObjectTypeCallback::FunctionIDXObjectTypeCallback(XPathExecutionContext&	theExecutionContext) :
	XObjectTypeCallback(),
	m_resultString(),
	m_executionContext(theExecutionContext)			
{
}



const XalanDOMString&
FunctionID::FunctionIDXObjectTypeCallback::processCallback(const XObject&	theXObject)
{
	theXObject.ProcessXObjectTypeCallback(*this);

	return m_resultString;
}



void
FunctionID::FunctionIDXObjectTypeCallback::Number(
			const XObject&	theXObject,
			double			/* theValue */)
{
	m_resultString = theXObject.str();
}



void
FunctionID::FunctionIDXObjectTypeCallback::Boolean(
			const XObject&	theXObject,
			bool			/* theValue */)
{
	m_resultString = theXObject.str();
}



void
FunctionID::FunctionIDXObjectTypeCallback::String(
			const XObject&			theXObject,
			const XalanDOMString&	/* theValue */)
{
	m_resultString = theXObject.str();
}



void
FunctionID::FunctionIDXObjectTypeCallback::ResultTreeFragment(
			const XObject&				theXObject,
			const ResultTreeFragBase&	/* theValue */)
{
	m_resultString = theXObject.str();
}



void
FunctionID::FunctionIDXObjectTypeCallback::ResultTreeFragment(
			const XObject&			theXObject,
			ResultTreeFragBase&		/* theValue */)
{
	m_resultString = theXObject.str();
}



void
FunctionID::FunctionIDXObjectTypeCallback::NodeSet(
			const XObject&			/* theXObject */,
			const NodeRefListBase&	theValue)
{
	const unsigned int	theNodeCount = theValue.getLength();

	for (unsigned int i = 0 ; i < theNodeCount; i++)
	{
		DOMServices::getNodeData(*theValue.item(i), m_resultString);

		append(m_resultString, XalanDOMChar(XalanUnicode::charSpace));			
	}
}



void
FunctionID::FunctionIDXObjectTypeCallback::Unknown(
			const XObject&			/* theObject */,
			const XalanDOMString&	/* theName */)
{
}


void
FunctionID::FunctionIDXObjectTypeCallback::Null(const XObject&		/* theObject */)
{
}