<?xml version="1.0" encoding="UTF-8"?> 
<xsl:stylesheet version="1.1"  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
    <html>
        <body>
            <h1>Employee(s) Database</h1>
            <table>
                <tr>
                    <th>Name</th>
                    <th>Department</th>
                    <th>Age</th>
                    <th>Gender</th>
                    <th>City</th>
                </tr>
                <xsl:for-each select="database/employee">
                    <tr>
                        <td><xsl:value-of select="name"/></td>
                        <td><xsl:value-of select="department"/></td>
                        <td><xsl:value-of select="age"/></td>
                        <td><xsl:value-of select="gender"/></td>
                        <td><xsl:value-of select="city"/></td>
                    </tr>
                </xsl:for-each>
            </table>
        </body>
    </html>
</xsl:template>
</xsl:stylesheet>