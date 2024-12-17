-- MySQL dump 10.13  Distrib 8.0.40, for Win64 (x86_64)
--
-- Host: localhost    Database: node_mysql_crud
-- ------------------------------------------------------
-- Server version	8.0.40

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `cryptos`
--

DROP TABLE IF EXISTS `cryptos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cryptos` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `symbol` varchar(100) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  PRIMARY KEY (`id`)
) 
ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cryptos`
--

LOCK TABLES `cryptos` WRITE;
/*!40000 ALTER TABLE `cryptos` DISABLE KEYS */;
INSERT INTO `cryptos` VALUES (1,'Bitcoin','BTC',50000.00),(2,'Ethereum','ETH',4000.00),(3,'Cardano','ADA',2.00),(4,'Polkadot','DOT',40.00),(5,'Solana','SOL',180.00),(6,'Binance Coin','BNB',600.00),(7,'Dogecoin','DOGE',0.25),(8,'XRP','XRP',1.10),(9,'Shiba Inu','SHIB',0.00),(10,'Avalanche','AVAX',100.00),(11,'Litecoin','LTC',200.00),(12,'Chainlink','LINK',30.00),(13,'Stellar','XLM',0.30),(14,'VeChain','VET',0.15),(15,'Uniswap','UNI',25.00),(16,'Aave','AAVE',300.00),(17,'Cosmos','ATOM',35.00),(18,'Algorand','ALGO',2.00),(19,'Decentraland','MANA',3.50),(20,'The Sandbox','SAND',5.00),(21,'Axie Infinity','AXS',150.00),(22,'FTX Token','FTT',60.00),(23,'Elrond','EGLD',400.00),(24,'Theta','THETA',7.00),(25,'Filecoin','FIL',70.00),(26,'Tezos','XTZ',5.00),(27,'Hedera','HBAR',0.35),(28,'PancakeSwap','CAKE',15.00),(29,'Near Protocol','NEAR',10.00),(30,'Harmony','ONE',0.20);
/*!40000 ALTER TABLE `cryptos` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-12-17 18:15:09
