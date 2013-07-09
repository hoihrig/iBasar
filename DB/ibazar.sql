-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.1.61-0ubuntu0.11.10.1


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema ibasar
--

CREATE DATABASE IF NOT EXISTS ibasar;
USE ibasar;

--
-- Definition of table `ibasar`.`Artikel`
--

DROP TABLE IF EXISTS `ibasar`.`Artikel`;
CREATE TABLE  `ibasar`.`Artikel` (
  `ID` int(10) unsigned NOT NULL,
  `Verkäufer` int(10) unsigned NOT NULL,
  `Size` varchar(10) NOT NULL,
  `Hersteller` int(10) unsigned NOT NULL,
  `Beschreibung` int(10) unsigned NOT NULL,
  `Preis` decimal(6,2) unsigned NOT NULL,
  `Aktiv` tinyint(1) NOT NULL,
  `Verkauft` tinyint(1) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Positionen der Verkäufer';

--
-- Dumping data for table `ibasar`.`Artikel`
--

/*!40000 ALTER TABLE `Artikel` DISABLE KEYS */;
LOCK TABLES `Artikel` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `Artikel` ENABLE KEYS */;


--
-- Definition of table `ibasar`.`Artikelbezeichnung`
--

DROP TABLE IF EXISTS `ibasar`.`Artikelbezeichnung`;
CREATE TABLE  `ibasar`.`Artikelbezeichnung` (
  `ID` int(10) unsigned NOT NULL,
  `Beschreibung` varchar(50) CHARACTER SET latin1 NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Liste der möglichen Artikel';

--
-- Dumping data for table `ibasar`.`Artikelbezeichnung`
--

/*!40000 ALTER TABLE `Artikelbezeichnung` DISABLE KEYS */;
LOCK TABLES `Artikelbezeichnung` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `Artikelbezeichnung` ENABLE KEYS */;


--
-- Definition of table `ibasar`.`Config`
--

DROP TABLE IF EXISTS `ibasar`.`Config`;
CREATE TABLE  `ibasar`.`Config` (
  `Logo` blob NOT NULL,
  `Provision_Verkauft` int(2) NOT NULL,
  `Provision_NVerkauft` int(2) NOT NULL,
  `Negativ` tinyint(1) NOT NULL,
  `WSymbol` char(1) CHARACTER SET latin1 NOT NULL,
  `Duplexprint` tinyint(1) NOT NULL,
  `Veranstaltung` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Systemeinstellungen, abhängig von Veranstaltung';

--
-- Dumping data for table `ibasar`.`Config`
--

/*!40000 ALTER TABLE `Config` DISABLE KEYS */;
LOCK TABLES `Config` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `Config` ENABLE KEYS */;


--
-- Definition of table `ibasar`.`Hersteller`
--

DROP TABLE IF EXISTS `ibasar`.`Hersteller`;
CREATE TABLE  `ibasar`.`Hersteller` (
  `ID` int(10) unsigned NOT NULL,
  `Hersteller` varchar(50) CHARACTER SET latin1 NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Liste der möglichen Hersteller';

--
-- Dumping data for table `ibasar`.`Hersteller`
--

/*!40000 ALTER TABLE `Hersteller` DISABLE KEYS */;
LOCK TABLES `Hersteller` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `Hersteller` ENABLE KEYS */;


--
-- Definition of table `ibasar`.`Veranstaltung`
--

DROP TABLE IF EXISTS `ibasar`.`Veranstaltung`;
CREATE TABLE  `ibasar`.`Veranstaltung` (
  `ID` int(10) unsigned NOT NULL,
  `Name` varchar(30) CHARACTER SET latin1 NOT NULL,
  `Datum` date NOT NULL,
  `Ort` varchar(50) CHARACTER SET latin1 NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ibasar`.`Veranstaltung`
--

/*!40000 ALTER TABLE `Veranstaltung` DISABLE KEYS */;
LOCK TABLES `Veranstaltung` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `Veranstaltung` ENABLE KEYS */;


--
-- Definition of table `ibasar`.`Verkäufer`
--

DROP TABLE IF EXISTS `ibasar`.`Verkäufer`;
CREATE TABLE  `ibasar`.`Verkäufer` (
  `ID` int(10) unsigned NOT NULL,
  `Vorname` varchar(30) CHARACTER SET latin1 NOT NULL,
  `Nachname` varchar(30) CHARACTER SET latin1 NOT NULL,
  `Straße` varchar(50) CHARACTER SET latin1 NOT NULL,
  `PLZ` int(5) unsigned NOT NULL,
  `Ort` varchar(50) CHARACTER SET latin1 NOT NULL,
  `Telefon` varchar(20) CHARACTER SET latin1 NOT NULL,
  `Email` varchar(50) CHARACTER SET latin1 NOT NULL,
  `Veranstaltung` int(11) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Liste der Verkäufer';

--
-- Dumping data for table `ibasar`.`Verkäufer`
--

/*!40000 ALTER TABLE `Verkäufer` DISABLE KEYS */;
LOCK TABLES `Verkäufer` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `Verkäufer` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
