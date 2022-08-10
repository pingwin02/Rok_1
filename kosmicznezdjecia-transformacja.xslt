<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:msxsl="urn:schemas-microsoft-com:xslt" exclude-result-prefixes="msxsl">
	
	<xsl:output method="xml" indent="yes"/>
	
	<xsl:template match="/">
		
		<xsl:element name="kosmicznezdjecia">

		<xsl:apply-templates select="kosmicznezdjecia/galeria"/>

		<xsl:apply-templates select="kosmicznezdjecia/ciala-niebieskie"/>
			
		<xsl:apply-templates select="kosmicznezdjecia/media"/>
			
		<xsl:apply-templates select="kosmicznezdjecia/autor"/>
			
		<xsl:apply-templates select="kosmicznezdjecia/linki"/>
			
		</xsl:element>
		
	</xsl:template>

	<xsl:template match="album">
		<xsl:element name="rok-{@year}">
			<xsl:copy-of select="naglowek"/>
				<xsl:apply-templates select="zdjecie"/>
		</xsl:element>
	</xsl:template>


	<xsl:template match="zdjecie">
		<xsl:element name="fot">
			<xsl:attribute name="nr">
				<xsl:value-of select="@id"/>
			</xsl:attribute>
			<xsl:element name="dane-osobowe">
				<xsl:apply-templates select="oautorze"/>
			</xsl:element>
			<xsl:copy-of select="obiekt"/>
			<xsl:copy-of select="miejsce"/>
			<xsl:copy-of select="data"/>
			<xsl:copy-of select="godzina"/>
			<xsl:call-template name="img"/>
			<xsl:copy-of select="komentarz"/>
		</xsl:element>
	</xsl:template>
	
	<xsl:template name="img">
		<xsl:element name="img">
			<xsl:attribute name="src">
				<xsl:value-of select="obraz/@zrodlo"/>
			</xsl:attribute>
			<xsl:attribute name="width">
				<xsl:text>100</xsl:text>
			</xsl:attribute>
		</xsl:element>
	</xsl:template>

	<xsl:template match="oautorze">
		<xsl:copy-of select="imie"/>
		<xsl:copy-of select="nazwisko"/>
		<xsl:copy-of select="email"/>
		<xsl:copy-of select="tel"/>
		<xsl:element name="{wyniki/@zgoda}">
			<xsl:text>ZGODA</xsl:text>
		</xsl:element>
	</xsl:template>

	<xsl:template match="ciala-niebieskie">
		<xsl:element name="baza-danych-obiektow">
			<xsl:copy-of select="naglowek"/>
			<xsl:apply-templates select="cialo"/>
		</xsl:element>
	</xsl:template>

	<xsl:template match="cialo">
		<xsl:variable name="typ" select="typ"/>
		<xsl:element name="obiekt{@n}">
			<xsl:element name="{translate($typ, ' ','')}">
				<xsl:value-of select="nazwa"/>
			</xsl:element>
		<xsl:element name="odkrywca">
			<xsl:attribute name="imie">
				<xsl:value-of select="odkrywca/imie"/>
				<xsl:if test="string-length(odkrywca/imie)=0">
				 <xsl:text>n/n</xsl:text>
				</xsl:if>
			</xsl:attribute>
			<xsl:attribute name="nazwisko">
				<xsl:value-of select="odkrywca/nazwisko"/>
				<xsl:if test="string-length(odkrywca/nazwisko)=0">
					<xsl:text>n/n</xsl:text>
				</xsl:if>
			</xsl:attribute>
		</xsl:element>
		<xsl:copy-of select="rok-odkrycia"/>
		<xsl:element name="odleglosc">
			<xsl:attribute name="{odleglosc/@jedn}">
				<xsl:text>unit</xsl:text>
			</xsl:attribute>
			<xsl:value-of select="odleglosc"/>
		</xsl:element>
		<xsl:copy-of select="link"/>
		</xsl:element>
	</xsl:template>
	
	<xsl:template match="media">
		<xsl:element name="media">
			<xsl:apply-templates select="obraz"/>
		</xsl:element>
	</xsl:template>
	
	<xsl:template match="obraz">
		<xsl:element name="img">
			<xsl:attribute name="src">
				<xsl:value-of select="@zrodlo"/>
			</xsl:attribute>
			<xsl:attribute name="width">
				<xsl:text>100</xsl:text>
			</xsl:attribute>
		</xsl:element>
	</xsl:template>
	
	<xsl:template match="autor">
		<xsl:copy>
			<xsl:element name="{imie}-{nazwisko}">
				<xsl:value-of select="indeks"/>
			</xsl:element>
		</xsl:copy>
	</xsl:template>
	
	<xsl:template match="linki">
		<xsl:copy>
			<xsl:apply-templates select="link"/>
		</xsl:copy>
	</xsl:template>
	
	<xsl:template match="link">
		<xsl:variable name="tytul" select="tytul"/>
		<xsl:copy>
			<xsl:element name="{translate($tytul, ' ','')}">
				<xsl:attribute name="cel">
					<xsl:value-of select="@zrodlo"/>
				</xsl:attribute>
				<xsl:value-of select="opis"/>
			</xsl:element>
		</xsl:copy>
	</xsl:template>
	
</xsl:stylesheet>