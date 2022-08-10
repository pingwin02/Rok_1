<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:msxsl="urn:schemas-microsoft-com:xslt" exclude-result-prefixes="msxsl">
	
	<xsl:output method="html" indent="yes"/>

	<xsl:template match="/">

	<html>
		<head>
		<meta charset="utf-8"/>
		<title>Kosmiczne zdjęcia - Baza danych</title>
		<meta content="Najciekawsze zdjęcia z kosmosu!" name="description"/>
		<meta content="width=device-width, height=device-height, initial-scale=1.0, user-scalable=yes" name="viewport"/>
		<link href="main.css" rel="Stylesheet" type="text/css"/>
		</head>

		<body>
			<div id="cointainer">
				<header>
					Baza danych strony Kosmiczne Zdjęcia!
				</header>
				<div id="tresc">
				<xsl:apply-templates select="kosmicznezdjecia/galeria/album"/>

				<h1>Baza autorów</h1>
					<xsl:call-template name="autorzy"/>

				<xsl:apply-templates select="kosmicznezdjecia/ciala-niebieskie"/>

				<h1>Media</h1>
					<ul>
					<xsl:apply-templates select="kosmicznezdjecia/media"/>
					</ul>

				<h1>Przydatne linki</h1>
					<xsl:apply-templates select="kosmicznezdjecia/linki"/>
					
				</div>
			<footer>
				<xsl:apply-templates select="kosmicznezdjecia/autor"/>
			</footer>
			</div>
		</body>
		
	</html>
	
	</xsl:template>

	<xsl:variable name="tabelaAlbum">
		<tr>
			<th>Id</th>
			<th>Autor</th>
			<th>Obiekt</th>
			<th>Miejsce</th>
			<th>Data</th>
			<th>Godzina</th>
			<th>Zdjęcie</th>
			<th>Komentarz</th>
		</tr>
	</xsl:variable>

	<xsl:variable name="tabelaAutorzy">
		<tr>
			<th>Numer</th>
			<th>Imię i nazwisko</th>
			<th>Email</th>
			<th>Telefon</th>
			<th>Zgoda na wyniki na mail?</th>
		</tr>
	</xsl:variable>

	<xsl:variable name="tabelaObiekty">
		<tr>
			<th>Numer</th>
			<th>Nazwa</th>
			<th>Typ</th>
			<th>Odkrywca</th>
			<th>Rok odkrycia</th>
			<th colspan="3">Odległość od Ziemi</th>
			<th>Dowiedz się więcej</th>
		</tr>
	</xsl:variable>

	<xsl:template match="autor">
		Copyright 2021-2022, <xsl:value-of select="imie"/> <xsl:text> </xsl:text> <xsl:value-of select="nazwisko"/> <xsl:text> </xsl:text> <xsl:value-of select="indeks"/>
	</xsl:template>

	<xsl:template match="album">
		<h1>
			<xsl:value-of select="naglowek"/>
		</h1>
		<table>
			<xsl:copy-of select="$tabelaAlbum" />
			<xsl:apply-templates select="zdjecie"/>
		</table>
	</xsl:template>

	<xsl:template match="zdjecie">
		<tr>
			<td>
				<xsl:value-of select="@id"/>
			</td>
			<td>
				<a>
					<xsl:attribute name="href">
						<xsl:text>#</xsl:text>
						<xsl:value-of select="@id"/>
					</xsl:attribute>
				<xsl:value-of select="oautorze/imie"/>
				<xsl:text> </xsl:text>
				<xsl:value-of select="oautorze/nazwisko"/>
				</a>
			</td>
			<td>
				<xsl:value-of select="obiekt"/>
			</td>
			<td>
				<xsl:value-of select="miejsce"/>
			</td>
			<td>
				<xsl:value-of select="data"/>
			</td>
			<td>
				<xsl:value-of select="godzina"/>
			</td>
			<td>
				<a target="_blank">
				<xsl:attribute name="href">
					<xsl:value-of select="obraz/@zrodlo"/>
				</xsl:attribute>
				<img class="srodek">
					<xsl:attribute name="src">
						<xsl:value-of select="obraz/@zrodlo"/>
					</xsl:attribute>
					<xsl:attribute name="alt">
						<xsl:value-of select="obiekt"/>
					</xsl:attribute>
				</img>	
				</a>
			</td>
			<td style="max-width:200px;">
				<xsl:choose>
					<xsl:when test="string-length(komentarz)!=0">
						<xsl:value-of select="normalize-space(komentarz)"/>
					</xsl:when>
					<xsl:otherwise>
						<em><xsl:text>brak</xsl:text></em>
					</xsl:otherwise>
				</xsl:choose>
			</td>
		</tr>
	</xsl:template>

	<xsl:template name="autorzy">
		<table>
			<xsl:copy-of select="$tabelaAutorzy" />
			<xsl:apply-templates select="kosmicznezdjecia/galeria/album/zdjecie/oautorze"/>
		</table>
	</xsl:template>

	<xsl:template match="wyniki[@zgoda='TAK']">
		<td style="background-color:green;">TAK</td>
	</xsl:template>

	<xsl:template match="wyniki[@zgoda='NIE']">
		<td style="background-color:red;">NIE</td>
	</xsl:template>

	<xsl:template match="oautorze">
		<tr>
			<xsl:attribute name="id">
				<xsl:number value="position()" format="1"/>
			</xsl:attribute>
			<td>
				<xsl:number value="position()" format="a)"/>
			</td>
			<td>
				<xsl:value-of select="imie"/>
				<xsl:text> </xsl:text>
				<xsl:value-of select="nazwisko"/>
			</td>
			<td>
				<a>
					<xsl:attribute name="href">
						<xsl:text>mailto:</xsl:text>
						<xsl:value-of select="email"/>
					</xsl:attribute>
					<xsl:value-of select="email"/>
				</a>
			</td>
			<td>
				<xsl:choose>
					<xsl:when test="string-length(tel)!=0">
						<a>
							<xsl:attribute name="href">
								<xsl:text>tel:</xsl:text>
								<xsl:value-of select="translate(tel,'-','')"/>
							</xsl:attribute>
							<xsl:value-of select="format-number(translate(tel,'-',''),'0')"/>
						</a>
					</xsl:when>
					<xsl:otherwise>
						<em>
							<xsl:text>brak</xsl:text>
						</em>
					</xsl:otherwise>
				</xsl:choose>
			</td>
			<xsl:apply-templates select="wyniki"/>
		</tr>
	</xsl:template>

	<xsl:template match="ciala-niebieskie">
		<h1>
			<xsl:value-of select="naglowek"/>
		</h1>
		<table>
			<xsl:copy-of select="$tabelaObiekty" />
			<xsl:for-each select="cialo">
				<xsl:sort select="nazwa"/>
				<tr>
				<td>
				<xsl:number value="position()" format="1."/>
				</td>
				<xsl:apply-templates select="."/>
				</tr>
			</xsl:for-each>
		</table>
	</xsl:template>

	<xsl:template match="cialo">
		<xsl:variable name="odl" select="odleglosc"/>
		<xsl:variable name="jedn" select="odleglosc/@jedn"/>
			<td>
				<xsl:value-of select="nazwa"/>
			</td>
			<td>
				<xsl:value-of select="typ"/>
			</td>
			<td>
				<xsl:choose>
					<xsl:when test="string-length(odkrywca)!=0">
							<xsl:value-of select="odkrywca"/>
					</xsl:when>
					<xsl:otherwise>
						<em>
							<xsl:text>n/n</xsl:text>
						</em>
					</xsl:otherwise>
				</xsl:choose>
			</td>
			<td>
				<xsl:value-of select="rok-odkrycia"/>
			</td>
			<td>
				<xsl:if test="$jedn='km'">
				<xsl:value-of select="format-number($odl,'###,###,##0')"/>
				</xsl:if>
				<xsl:if test="$jedn='au'">
					<xsl:value-of select="format-number($odl * 150000000,'###,###,##0')"/>
				</xsl:if>
				<xsl:if test="$jedn='ly'">
					<xsl:value-of select="format-number($odl * 9500000000000,'###,###,##0')"/>
				</xsl:if>
				<xsl:text> km</xsl:text>
			</td>
			<td>
				<xsl:if test="$jedn='km'">
					<xsl:value-of select="format-number($odl div 9500000000000,'###,###,##0')"/>
				</xsl:if>
				<xsl:if test="$jedn='au'">
					<xsl:value-of select="format-number($odl div 63241,'###,###,##0')"/>
				</xsl:if>
				<xsl:if test="$jedn='ly'">
					<xsl:value-of select="format-number($odl,'###,###,##0')"/>
				</xsl:if>
				<xsl:text> ly</xsl:text>
			</td>
			<td>
				<xsl:if test="$jedn='km'">
					<xsl:value-of select="format-number($odl div 150000000,'###,###,##0')"/>
				</xsl:if>
				<xsl:if test="$jedn='au'">
					<xsl:value-of select="$odl"/>
				</xsl:if>
				<xsl:if test="$jedn='ly'">
					<xsl:value-of select="format-number($odl * 63241,'###,###,##0')"/>
				</xsl:if>
				<xsl:text> au</xsl:text>
			</td>
			<td>
				<a target="_blank">
					<xsl:attribute name="href">
						<xsl:value-of select="link/@zrodlo"/>
					</xsl:attribute>
					<xsl:value-of select="link"/>
				</a>
			</td>
	</xsl:template>

	<xsl:template match="obraz">
		<li>
		<a target="_blank">
			<xsl:attribute name="href">
				<xsl:value-of select="@zrodlo"/>
			</xsl:attribute>
			<img>
				<xsl:attribute name="src">
					<xsl:value-of select="@zrodlo"/>
				</xsl:attribute>
				<xsl:attribute name="alt">
					<xsl:value-of select="@podpis"/>
				</xsl:attribute>
			</img>
		</a>
			<p><xsl:value-of select="@podpis"/></p>
		</li>
	</xsl:template>

	<xsl:template match="link">
		<p>
			<a>
				<xsl:attribute name="href">
					<xsl:value-of select="@zrodlo"/>
				</xsl:attribute>
				<xsl:value-of select="tytul"/>
			</a>
			<xsl:text> - </xsl:text>
			<xsl:value-of select="opis"/>
		</p>
	</xsl:template>
	
	
</xsl:stylesheet>