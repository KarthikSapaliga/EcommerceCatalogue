-- MySQL dump 10.13  Distrib 8.0.39, for Linux (x86_64)
--
-- Host: localhost    Database: Ecommerce
-- ------------------------------------------------------
-- Server version	8.0.39-0ubuntu0.24.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Cart`
--

DROP TABLE IF EXISTS `Cart`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Cart` (
  `UserID` int DEFAULT NULL,
  `ProductID` int DEFAULT NULL,
  KEY `UserID` (`UserID`),
  KEY `ProductID` (`ProductID`),
  CONSTRAINT `Cart_ibfk_1` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`) ON DELETE CASCADE,
  CONSTRAINT `Cart_ibfk_2` FOREIGN KEY (`ProductID`) REFERENCES `Products` (`ProductNum`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Cart`
--

LOCK TABLES `Cart` WRITE;
/*!40000 ALTER TABLE `Cart` DISABLE KEYS */;
INSERT INTO `Cart` VALUES (62,2),(62,1),(62,6);
/*!40000 ALTER TABLE `Cart` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Products`
--

DROP TABLE IF EXISTS `Products`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Products` (
  `ProductNum` int NOT NULL AUTO_INCREMENT,
  `ProductName` varchar(50) NOT NULL,
  `Description` text,
  `Category` varchar(20) DEFAULT NULL,
  `Rating` float DEFAULT NULL,
  `Purchases` int DEFAULT NULL,
  `Stock` int DEFAULT NULL,
  `Price` decimal(10,2) DEFAULT NULL,
  `Discount` decimal(5,2) DEFAULT NULL,
  `SellerID` int DEFAULT NULL,
  PRIMARY KEY (`ProductNum`),
  UNIQUE KEY `ProductName` (`ProductName`),
  KEY `SellerID` (`SellerID`),
  CONSTRAINT `Products_ibfk_1` FOREIGN KEY (`SellerID`) REFERENCES `Users` (`UserID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=86 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Products`
--

LOCK TABLES `Products` WRITE;
/*!40000 ALTER TABLE `Products` DISABLE KEYS */;
INSERT INTO `Products` VALUES (1,'IKEA KIVIK Sofa','Comfortable and spacious sofa with durable fabric upholstery and deep seating','Furniture',4.8,150,237,25000.00,9.00,1),(2,'Ashley Furniture Signature Design','Contemporary sofa with plush cushions and tufted backrest for modern living rooms','Furniture',4.7,145,208,23000.00,9.00,2),(3,'Wayfair Custom Upholstery','Customizable sofa with wide range of fabric options and reversible cushions for versatility','Furniture',4.6,140,199,22000.00,9.00,3),(4,'West Elm Harmony Sofa','Stylish sofa with eco-friendly construction and feather-wrapped cushions for luxurious comfort','Furniture',4.5,135,190,21000.00,9.00,4),(5,'Joybird Eliot Sofa','Mid-century modern sofa with hardwood frame and tailored upholstery for timeless appeal','Furniture',4.4,130,179,20000.00,9.00,5),(6,'Zinus Upholstered Platform Bed','Minimalist bed frame with upholstered headboard and sturdy wooden slats for support','Furniture',4.9,200,298,35000.00,9.50,6),(7,'Novogratz Marion Canopy Bed','Elegant canopy bed with metal frame and decorative finials for a touch of romance','Furniture',4.8,195,290,33000.00,9.00,7),(8,'IKEA MALM Bed Frame','Classic bed frame with storage drawers and adjustable bed sides for customized comfort','Furniture',4.7,190,280,32000.00,9.00,1),(9,'Modway Emily Upholstered Bed','Contemporary bed with tufted headboard and solid wood slats for mattress support','Furniture',4.6,185,270,31000.00,9.00,8),(10,'Casper Wave Hybrid Mattress','Luxurious hybrid mattress with advanced ergonomic support and breathable foam layers','Furniture',4.5,180,260,30000.00,9.00,9),(11,'Travel Backpack','Durable travel backpack with multiple compartments','Lifestyle',4.7,400,80,1800.00,20.00,51),(12,'Dell Inspiron','Versatile laptop suitable for work and entertainment','Electronics',4.8,124,180,55000.00,8.00,11),(13,'Lenovo ThinkPad','Reliable laptop with robust build quality for professional use','Electronics',4.9,130,190,60000.00,9.00,12),(14,'Asus ROG Strix','Gaming powerhouse with high-performance graphics and immersive sound','Electronics',4.7,140,220,75000.00,9.00,14),(15,'Acer Swift','Lightweight and portable laptop perfect for students and professionals on the go','Electronics',4.6,128,169,45000.00,8.50,15),(16,'Microsoft Surface Laptop','Stylish and sleek laptop with a detachable touchscreen for versatility','Electronics',4.8,132,200,70000.00,9.00,16),(17,'HP Spectre x360','Premium convertible laptop with 360-degree hinge for multiple usage modes','Electronics',4.9,138,210,78000.00,9.50,10),(18,'Samsung Galaxy Book','Innovative laptop with S Pen support and vibrant AMOLED display','Electronics',4.7,134,190,67000.00,9.00,17),(19,'Razer Blade','Ultra-thin gaming laptop with customizable RGB lighting and powerful performance','Electronics',4.8,142,230,85000.00,9.00,18),(20,'Google Pixelbook','Premium Chromebook with Google Assistant integration and Pixel Pen compatibility','Electronics',4.6,126,180,60000.00,9.00,19),(21,'Samsung Galaxy S21','Flagship smartphone with stunning AMOLED display and powerful camera system','Electronics',4.8,120,180,80000.00,9.00,17),(22,'Apple iPhone 13 Pro','Premium iPhone with ProMotion display and enhanced photography features','Electronics',4.9,125,213,90000.00,9.50,13),(23,'OnePlus 10 Pro','High-performance smartphone with smooth 120Hz refresh rate and Hasselblad camera','Electronics',4.8,128,210,85000.00,9.00,20),(24,'Google Pixel 6','Innovative smartphone with Tensor chip and exceptional camera capabilities','Electronics',4.7,122,190,75000.00,9.00,19),(25,'Xiaomi Mi 12','Feature-packed smartphone with Snapdragon processor and high-resolution display','Electronics',4.8,130,220,78000.00,12.00,21),(26,'Huawei P50 Pro','Premium flagship with Leica quad-camera setup and Kirin chipset','Electronics',4.7,125,210,82000.00,9.00,22),(27,'Sony Xperia 5 III','Compact powerhouse with 120Hz OLED display and pro-grade camera features','Electronics',4.8,126,200,79000.00,9.00,23),(28,'Oppo Find X5 Pro','Sleek smartphone with curved display and AI-enhanced camera system','Electronics',4.7,124,190,77000.00,11.00,24),(29,'Realme GT 2 Pro','Performance-oriented smartphone with Snapdragon 8 Gen 1 processor and 150W fast charging','Electronics',4.8,132,220,83000.00,9.00,25),(30,'Motorola Edge 30 Pro','Feature-rich smartphone with 144Hz AMOLED display and triple-camera setup','Electronics',4.7,128,210,80000.00,9.00,26),(31,'LG OLED C1','Premium OLED TV with stunning picture quality and Dolby Vision IQ','Electronics',4.9,150,220,100000.00,9.50,27),(32,'Sony Bravia XR A90J','High-end 4K TV with Cognitive Processor XR and Acoustic Surface Audio+','Electronics',4.8,145,210,95000.00,9.00,23),(33,'Samsung QN90A Neo QLED','Flagship QLED TV with Quantum Matrix Technology and Object Tracking Sound','Electronics',4.8,148,230,98000.00,9.00,17),(34,'TCL 6-Series','Feature-packed Roku TV with QLED display and Dolby Vision HDR','Electronics',4.7,140,200,80000.00,8.00,28),(35,'Hisense U8G','Ultra-bright ULED TV with Full Array Local Dimming and Dolby Atmos','Electronics',4.6,135,190,75000.00,9.00,29),(36,'Vizio P-Series Quantum X','High-performance 4K TV with Quantum Dot technology and Active Full Array backlighting','Electronics',4.7,138,209,85000.00,16.00,30),(37,'Panasonic JZ2000','Premium OLED TV with HCX Pro AI Processor and Dolby Atmos','Electronics',4.8,142,220,92000.00,9.00,31),(38,'Philips OLED 806','Ambilight OLED TV with P5 AI Perfect Picture Engine and Dolby Vision + Atmos','Electronics',4.7,137,210,90000.00,9.00,32),(39,'Sharp Aquos 8K','Ultra-high-definition TV with 8K resolution and HDR10+ support','Electronics',4.6,130,200,85000.00,11.00,33),(40,'Skyworth Q91','Slim and stylish QLED TV with Dolby Vision and Dolby Atmos','Electronics',4.6,132,190,80000.00,9.00,34),(41,'Apple Watch Series 7','Premium smartwatch with larger display and advanced health tracking features','Electronics',4.9,140,218,6000.00,9.00,13),(42,'Samsung Galaxy Watch 4','Feature-rich smartwatch with Wear OS and comprehensive fitness tracking','Electronics',4.8,135,210,5500.00,10.00,17),(43,'Fitbit Sense','Health-focused smartwatch with EDA sensor and ECG app for stress management and heart health','Electronics',4.7,130,200,4500.00,9.00,35),(44,'Garmin Fenix 7','Multisport GPS smartwatch with rugged design and advanced training features','Electronics',4.8,145,230,6500.00,13.00,36),(45,'Huawei Watch GT 3','Stylish smartwatch with long battery life and SpO2 monitoring for fitness enthusiasts','Electronics',4.6,125,190,5000.00,8.50,22),(46,'Orient Electric Aeroquiet','Sleek and silent ceiling fan with aerodynamic profile for efficient air delivery','Home Appliances',4.8,95,180,4000.00,9.00,37),(47,'Havells Stealth','High-speed ceiling fan with unique blade design for maximum air thrust','Home Appliances',4.7,90,170,3800.00,9.00,38),(48,'Bajaj Edge','Energy-efficient ceiling fan with anti-dust coating for easy maintenance','Home Appliances',4.6,85,160,3500.00,9.00,39),(49,'Usha Striker Platinum','Decorative ceiling fan with metallic finish and powerful motor for uniform air circulation','Home Appliances',4.5,80,150,3200.00,9.00,40),(50,'LG Dual Inverter','Energy-efficient split AC with dual rotary compressor and 4-in-1 convertible cooling','Home Appliances',4.9,200,297,45000.00,9.50,27),(51,'Voltas All Star Inverter','High-performance split AC with eco-friendly refrigerant and advanced air purification','Home Appliances',4.8,190,290,43000.00,9.00,41),(52,'Daikin Neo Swing','Silent operation split AC with neo swing compressor for smoother rotation and durability','Home Appliances',4.7,185,280,42000.00,12.50,42),(53,'Blue Star Inverter','Smart split AC with precision cooling technology and self-clean feature for hassle-free maintenance','Home Appliances',4.6,180,270,41000.00,11.50,43),(54,'Samsung Wind-Free','Innovative split AC with wind-free cooling and AI-based optimization for energy efficiency','Home Appliances',4.5,175,260,40000.00,8.00,17),(55,'Symphony Diet 35T','Sleek tower cooler with multi-stage filtration and powerful air throw for effective cooling','Home Appliances',4.8,100,180,12000.00,9.00,44),(56,'Crompton Ozone 75','Desert cooler with honeycomb cooling pads and large water tank capacity for longer cooling','Home Appliances',4.7,95,170,11000.00,8.00,45),(57,'Bajaj DC 2016 Glacier','Personal cooler with turbofan technology and ice chamber for instant cooling','Home Appliances',4.6,90,160,10000.00,12.00,39),(58,'Kenstar Double Cool','Window cooler with double blower technology and auto-fill feature for convenience','Home Appliances',4.5,85,150,9500.00,13.00,46),(59,'Havells Fresco i','Tower cooler with intelligent air delivery and dust filter for clean and fresh air','Home Appliances',4.4,80,140,9000.00,16.00,38),(60,'Face Cream','Moisturizing face cream for daily use','Beauty',4.5,500,96,1100.00,10.00,47),(61,'Lip Balm','Natural lip balm with shea butter','Beauty',4.2,300,50,350.00,0.00,48),(62,'Eye Liner','Waterproof black eyeliner','Beauty',4.7,400,80,250.00,15.00,48),(63,'Hair Brush','Detangling hair brush with soft bristles','Beauty',4.6,350,60,500.00,10.00,49),(64,'Sunscreen SPF 30','Non-greasy sunscreen lotion','Beauty',4.4,600,117,800.00,5.00,47),(65,'Baby Onesie','Soft cotton onesie for infants','Kids',4.8,200,30,750.00,5.00,50),(66,'Kids Backpack','Colorful backpack for school or travel','Kids',4.6,400,78,1400.00,15.00,51),(67,'Building Blocks Set','Educational building blocks toy for kids','Kids',4.9,350,70,1200.00,0.00,52),(68,'Childrens Book','Interactive storybook for young readers','Kids',4.3,250,40,300.00,20.00,53),(69,'Yoga Mat','Non-slip yoga mat for fitness enthusiasts','Lifestyle',4.7,350,60,1600.00,20.00,54),(70,'Scented Candle','Vanilla scented candle for relaxation','Lifestyle',4.3,250,40,500.00,0.00,50),(71,'Glass Water Bottle','Eco-friendly glass water bottle','Lifestyle',4.5,300,50,700.00,10.00,2),(72,'Wireless Earbuds','Bluetooth wireless earbuds with charging case','Lifestyle',4.8,450,85,2000.00,15.00,23),(73,'Portable Charger','Compact portable charger for smartphones','Lifestyle',4.6,400,80,1000.00,5.00,55),(74,'Face Mask Set','Set of hydrating face masks','Beauty',4.4,350,69,900.00,0.00,56),(75,'Kids T-Shirt','Comfortable cotton t-shirt for kids','Kids',4.5,300,60,400.00,10.00,51),(76,'Perfume','Floral-scented perfume for women','Beauty',4.2,200,40,1500.00,15.00,50),(77,'Stuffed Animal','Soft plush toy for children','Kids',4.7,250,50,600.00,0.00,57),(78,'Protein Shaker Bottle','Shaker bottle for protein shakes and smoothies','Lifestyle',4.6,300,60,550.00,5.00,58),(79,'Cleansing Wipes','Refreshing facial cleansing wipes','Beauty',4.3,400,80,300.00,10.00,59),(80,'Toy Car Set','Remote-controlled toy car set for kids','Kids',4.8,350,70,1200.00,0.00,60),(81,'Cookbook','Healthy recipes cookbook for families','Lifestyle',4.5,200,40,700.00,15.00,55),(82,'Hand Cream','Moisturizing hand cream with shea butter','Beauty',4.6,300,60,400.00,5.00,47);
/*!40000 ALTER TABLE `Products` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Users`
--

DROP TABLE IF EXISTS `Users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Users` (
  `UserID` int NOT NULL AUTO_INCREMENT,
  `UserName` varchar(20) NOT NULL,
  `Password` varchar(20) NOT NULL,
  `UserType` enum('BUYER','SELLER') NOT NULL,
  PRIMARY KEY (`UserID`),
  UNIQUE KEY `userName` (`UserName`)
) ENGINE=InnoDB AUTO_INCREMENT=66 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Users`
--

LOCK TABLES `Users` WRITE;
/*!40000 ALTER TABLE `Users` DISABLE KEYS */;
INSERT INTO `Users` VALUES (1,'IKEA','IKEAPass@123','SELLER'),(2,'Ashley','AshleyPass@123','SELLER'),(3,'Wayfair','WayfairPass@123','SELLER'),(4,'West','WestPass@123','SELLER'),(5,'Joybird','JoybirdPass@123','SELLER'),(6,'Zinus','ZinusPass@123','SELLER'),(7,'Novogratz','NovogratzPass@123','SELLER'),(8,'Modway','ModwayPass@123','SELLER'),(9,'Casper','CasperPass@123','SELLER'),(10,'HP','HPPass@123','SELLER'),(11,'Dell','DellPass@123','SELLER'),(12,'Lenovo','LenovoPass@123','SELLER'),(13,'Apple','ApplePass@123','SELLER'),(14,'Asus','AsusPass@123','SELLER'),(15,'Acer','AcerPass@123','SELLER'),(16,'Microsoft','MicrosoftPass@123','SELLER'),(17,'Samsung','SamsungPass@123','SELLER'),(18,'Razer','RazerPass@123','SELLER'),(19,'Google','GooglePass@123','SELLER'),(20,'OnePlus','OnePlusPass@123','SELLER'),(21,'Xiaomi','XiaomiPass@123','SELLER'),(22,'Huawei','HuaweiPass@123','SELLER'),(23,'Sony','SonyPass@123','SELLER'),(24,'Oppo','OppoPass@123','SELLER'),(25,'Realme','RealmePass@123','SELLER'),(26,'Motorola','MotorolaPass@123','SELLER'),(27,'LG','LGPass@123','SELLER'),(28,'TCL','TCLPass@123','SELLER'),(29,'Hisense','HisensePass@123','SELLER'),(30,'Vizio','VizioPass@123','SELLER'),(31,'Panasonic','PanasonicPass@123','SELLER'),(32,'Philips','PhilipsPass@123','SELLER'),(33,'Sharp','SharpPass@123','SELLER'),(34,'Skyworth','SkyworthPass@123','SELLER'),(35,'Fitbit','FitbitPass@123','SELLER'),(36,'Garmin','GarminPass@123','SELLER'),(37,'Orient','OrientPass@123','SELLER'),(38,'Havells','HavellsPass@123','SELLER'),(39,'Bajaj','BajajPass@123','SELLER'),(40,'Usha','UshaPass@123','SELLER'),(41,'Voltas','VoltasPass@123','SELLER'),(42,'Daikin','DaikinPass@123','SELLER'),(43,'BlueStar','BlueStarPass@123','SELLER'),(44,'Symphony','SymphonyPass@123','SELLER'),(45,'Crompton','CromptonPass@123','SELLER'),(46,'Kenstar','KenstarPass@123','SELLER'),(47,'Dove','DovePass@123','SELLER'),(48,'MamaEarth','MamaEarthPass@123','SELLER'),(49,'ManMatters','ManMattersPass@123','SELLER'),(50,'Flora','FloraPass@123','SELLER'),(51,'WildCraft','WildCraftPass@123','SELLER'),(52,'Lego','LegoPass@123','SELLER'),(53,'Classmate','ClassmatePass@123','SELLER'),(54,'KP','KPPass@123','SELLER'),(55,'Portronics','PortronicsPass@123','SELLER'),(56,'Nivea','NiveaPass@123','SELLER'),(57,'Stuffy','StuffyPass@123','SELLER'),(58,'MuscleBlaze','MuscleBlazePass@123','SELLER'),(59,'Dettol','DettolPass@123','SELLER'),(60,'Hot-Weels','Hot-WeelsPass@123','SELLER'),(61,'user1','user1pass@123','BUYER'),(62,'a','a','BUYER'),(64,'s','s','SELLER');
/*!40000 ALTER TABLE `Users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Wishlist`
--

DROP TABLE IF EXISTS `Wishlist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Wishlist` (
  `UserID` int DEFAULT NULL,
  `ProductID` int DEFAULT NULL,
  KEY `UserID` (`UserID`),
  KEY `ProductID` (`ProductID`),
  CONSTRAINT `Wishlist_ibfk_1` FOREIGN KEY (`UserID`) REFERENCES `Users` (`UserID`) ON DELETE CASCADE,
  CONSTRAINT `Wishlist_ibfk_2` FOREIGN KEY (`ProductID`) REFERENCES `Products` (`ProductNum`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Wishlist`
--

LOCK TABLES `Wishlist` WRITE;
/*!40000 ALTER TABLE `Wishlist` DISABLE KEYS */;
INSERT INTO `Wishlist` VALUES (62,6),(62,50);
/*!40000 ALTER TABLE `Wishlist` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-08-11  4:32:31
