/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
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
#if !defined(XALAN_STYLESHEETROOT_HEADER_GUARD)
#define XALAN_STYLESHEETROOT_HEADER_GUARD 



// Base include file.  Must be first.
#include "XSLTDefinitions.hpp"



#include "Stylesheet.hpp"



#include <XalanDOM/XalanDOMString.hpp>



#include <PlatformSupport/FormatterListener.hpp>



class StylesheetConstructionContext;
class XSLTResultTarget;



/**
 * This acts as the stylesheet root of the stylesheet 
 * tree, and holds values that are shared by all 
 * stylesheets in the tree.
 */
class XALAN_XSLT_EXPORT StylesheetRoot : public Stylesheet
{
public:

	/**
	 * Construct a Stylesheet from a Document.
	 *
	 * @param baseIdentifier document identifier
	 * @param constructionContext context for construction of object
	 */
	StylesheetRoot(
        const XalanDOMString&			baseIdentifier,
		StylesheetConstructionContext&	constructionContext);    

	virtual 
	~StylesheetRoot();

	/**
	 * Called after construction is completed.
	 */
	virtual void
	postConstruction(StylesheetConstructionContext&		constructionContext);

	/**
	 * Transform the source tree to the output in the given result tree target.
	 *
	 * @param inputSource  The input source tree
	 * @param outputTarget The output source tree
	 * @param constructionContext context for construction of object
	 */
	void
	process(
			XalanNode*						sourceTree,
			XSLTResultTarget&				outputTarget,
			StylesheetExecutionContext&		executionContext) const;

	/**
	 * Have the stylesheet create the appropriate FormatterListener,
	 * based on the XSLTResultTarget provided.  setupFormatterListener
	 * also calls setFormatterListener() on the execution context
	 * instance.  setupFormatterListener() is done automatically by
	 * process(), but this is provided as an escape, to allow for
	 * changing the FormatterListener on-the-fly.
	 *
	 * @param outputTarget The output source tree
	 * @param constructionContext context for construction of object
	 * @return a pointer to the new FormatterListener instance.
	 */
	FormatterListener*
	setupFormatterListener(
			XSLTResultTarget&				outputTarget,
			StylesheetExecutionContext&		executionContext) const;

	/** 
	 * Return the output method that was specified in the stylesheet. 
	 * The returned value is one of FormatterLister::eFormat values.
	 *
	 * @return value of output method
	 */
	FormatterListener::eFormat
	getOutputMethod() const
	{
		return m_outputMethod;
	}

	bool
	isOutputMethodSet() const
	{
		return getOutputMethod() == FormatterListener::OUTPUT_METHOD_NONE ? false : true;
	}

	/**
	 * Get the output version string that was specified in the
	 * xsl:output element
	 *
	 * @return output version string
	 */
	XalanDOMString
	getOutputVersion() const
	{ 
		return m_version;
	}

	/**
	 * Determine if output indenting was specified in the
	 * xsl:output element
	 *
	 * @return true to indent
	 */
	bool 
	getOutputIndent() const
	{
		return m_indentResult;
	}

	/**
	 * Get the output encoding string that was specified in the
	 * xsl:output element
	 *
	 * @return encoding string
	 */
	XalanDOMString 
	getOutputEncoding() const
	{
		return m_encoding;
	}

	/**
	 * Get the media-type string that was specified in the 
	 * xsl:output element
	 *
	 * @return media type string
	 */
	XalanDOMString 
	getOutputMediaType() const
	{
		return m_mediatype;
	}

	/**
	 * Get the doctype-system-id string that was specified in the 
	 * xsl:output element
	 *
	 * @return document type string
	 */
	XalanDOMString 
	getOutputDoctypeSystem() const
	{
		return m_doctypeSystem;
	}

	/**
	 * Get the doctype-public-id string that was specified in the 
	 * xsl:output element
	 *
	 * @return document type public id string
	 */
	XalanDOMString 
	getOutputDoctypePublic() const
	{
		return m_doctypePublic;
	}

	/**
	 * Determine whether to output XML declarations.
	 *
	 * @return true to output declarations
	 */
	bool
	getOmitOutputXMLDecl() const
	{
		return m_omitxmlDecl;
	}

	/**
	 * Get the standalone string that was specified in the 
	 * xsl:output element.(either "yes" or "no")
	 *
	 * @return standalone string
	 */
	XalanDOMString
	getOutputStandalone() const
	{
		return m_standalone;
	}

	/**
	 * Get the template representing the default rule for text.
	 *
	 * @return pointer to template rule for text
	 */
	ElemTemplate* 
	getDefaultTextRule() const
	{
		return m_defaultTextRule;
	}

	/**
	 * Get the template representing the default rule.
	 *
	 * @return pointer to default template rule
	 */
	ElemTemplate* 
	getDefaultRule() const
	{
		return m_defaultRule;
	}

	/**
	 * Get the template representing the default root rule.
	 *
	 * @return pointer to default root template rule
	 */
	ElemTemplate* 
	getDefaultRootRule() const
	{
		return m_defaultRootRule;
	}

	/**
	 * Process the "xsl:output" element.
	 *
	 * @param name                name of element
	 * @param atts                attribute list for element
	 * @param constructionContext context for construction of object
	 */
	void 
	processOutputSpec(
			const XalanDOMChar*				name, 
			const AttributeList&			atts,
			StylesheetConstructionContext&	constructionContext);

	/**
	 * Create the default rule if needed.
	 *
	 * @param constructionContext context for construction of object
	 */
	void 
	initDefaultRule(StylesheetConstructionContext&	constructionContext);

	/**
	 * The version tells the version of XML to be used for outputting the result tree,
	 * as specified in xsl:output.
	 */
	XalanDOMString	m_version;

	/**
	 * indent-result is by default no, which means an XSL processor must not
	 * change the whitespace on output.
	 */
	bool			m_indentResult;

	/**
	 * The encoding attribute specifies the preferred encoding to use 
	 * for outputting the result tree. 
	 */
	XalanDOMString	m_encoding;

	/**
	 * The media-type attribute is applicable for the xml output method. 
	 * The default value for the media-type attribute is text/xml.
	 */
	XalanDOMString	m_mediatype;

	/**
	 * If the doctype-system-id attribute is specified, the xml output method should 
	 * output a document type declaration immediately before the first element. 
	 * The name following <!DOCTYPE should be the name of the first element. 
	 */
	XalanDOMString	m_doctypeSystem;

	/**
	 * If doctype-public-id attribute is also specified, then the xml output 
	 * method should output PUBLIC followed by the public identifier and then 
	 * the system identifier; otherwise, it should output SYSTEM followed by 
	 * the system identifier. The internal subset should be empty. The 
	 * doctype-public-id attribute should be ignored unless the doctype-system-id 
	 * attribute is specified.
	 */
	XalanDOMString	m_doctypePublic;

	/**
	 * Tells whether or not to output an XML declaration.
	 */
	bool			m_omitxmlDecl;

	/**
	 * Tells what the xmldecl should specify for the standalone value.
     */
	XalanDOMString	m_standalone;

	/**
	 * Retrieve the stack of imported stylesheets.
	 * 
	 * @return stack of URIs for stylesheets
	 */
	URLStackType&
	getImportStack()
	{
		return m_importStack;
	}

	/**
	 * Retrieve the stack of imported stylesheets.
	 * 
	 * @return const stack of URIs for stylesheets
	 */
	const URLStackType&
	getImportStack() const
	{
		return m_importStack;
	}

	/**
	 * Change the value of the flag for indenting results.
	 * 
	 * @param bIndent true to indent results
	 */
	void
	setIndentResult(bool bIndent)
	{
		m_indentResult = bIndent;
	}

	/**
	 * Change the value of the output method, one of the
	 * FormatterListener::eFormat values.
	 * 
	 * @param meth new method number
	 */
	void
	setOutputMethod(FormatterListener::eFormat	meth)
	{
		m_outputMethod = meth;
	}

	bool
	hasCDATASectionElements() const
	{
		assert(m_hasCdataSectionElems == false && m_cdataSectionElems.size() == 0 ||
			   m_hasCdataSectionElems == true && m_cdataSectionElems.size() != 0);

		return m_hasCdataSectionElems;
	}

	/**
	 * Determine if a QName is in the list of CDATA section
	 * element QNames.
	 * 
	 * @param theQName The QName of the element to check.
	 * @return true or false
	 */
	bool
	isCDATASectionElementName(const XalanQName&		theQName) const;

	/**
	 * Given a valid element key, return the corresponding node list.
	 *
	 * @param doc			   source document
	 * @param name			   name of the key, which must match the 'name'
	 *						   attribute on xsl:key
	 * @param ref			   value that must match the value found by the
	 *						   'match' attribute on xsl:key
	 * @param resolver		   resolver for namespace resolution
	 * @param nodelist         A node list to contain the nodes found
	 * @param executionContext current execution context
	 */
	void
	getNodeSetByKey(
			XalanNode*						doc,
			const XalanDOMString&			name,
			const XalanDOMString&			ref,
			const PrefixResolver&			resolver,
			MutableNodeRefList&				nodelist,
			StylesheetExecutionContext&		executionContext,
			KeyTablesTableType&				theKeysTable) const;

private:

	/**
	 * The URL that belongs to the result namespace.
	 * @serial
	 */
	XalanDOMString				m_resultNameSpaceURL;

	/**
	 * The output method as specified in xsl:output.
	 */
	FormatterListener::eFormat	m_outputMethod;

	/**
	 * List of qnames that specifies elements that should be formatted 
	 * as CDATA.
	 */
	QNameVectorType				m_cdataSectionElems;

	bool						m_hasCdataSectionElems;

	/**
	 * A stack of who's importing whom is needed in order to detect 
	 * a recursive include or import, which is an error.
	 */
	URLStackType				m_importStack;


	/**
	 * The default template to use for text nodes if we don't find 
	 * anything else.  This is initialized in initDefaultRule().
	 */
	ElemTemplate*				m_defaultTextRule;

	/**
	 * The default template to use if we don't find anything
	 * else.  This is initialized in initDefaultRule().
	 */
	ElemTemplate*				m_defaultRule;

	/**
	 * The default template to use for the root if we don't find 
	 * anything else.  This is initialized in initDefaultRule().
	 */
	ElemTemplate*				m_defaultRootRule;

	/**
	 * This is set to true if an xsl:key directive is found.
	 */
	bool						m_needToBuildKeysTable;

    // Not implemented...
    StylesheetRoot(const StylesheetRoot&);

    StylesheetRoot&
    operator=(const StylesheetRoot&);

    bool
    operator==(const StylesheetRoot&) const;
};



#endif	// XALAN_STYLESHEETROOT_HEADER_GUARD