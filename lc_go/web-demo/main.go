package main

import (
	"gorm.io/gorm"
	"log"
	"web-demo/config"
	"web-demo/handler"
	"web-demo/repository"
	"web-demo/service"

	"github.com/gin-gonic/gin"
)

// 全局数据库连接
var db *gorm.DB
var productController handler.ProductHandler

func main() {
	// 数据库配置
	dbConfig := config.DatabaseConfig{
		Host:     "localhost",
		Port:     "3306",
		User:     "root",           // 替换为你的数据库用户名
		Password: "123456",         // 替换为你的数据库密码
		DBName:   "review_sharded", // 替换为你的数据库名
	}

	// 初始化数据库连接
	db, err := config.InitDatabase(dbConfig)
	if err != nil {
		log.Fatal("Failed to connect to database:", err)
	}

	// 初始化各层
	productRepo := repository.NewProductRepository(db)
	productService := service.NewProductService(productRepo)
	productHandler := handler.NewProductHandler(productService)

	// 初始化 Gin 路由
	r := gin.Default()

	// 产品相关路由
	api := r.Group("/api/v1")
	{
		products := api.Group("/products")
		{
			products.POST("/", productHandler.CreateProduct)
			products.GET("/:id", productHandler.GetProduct)
			products.GET("/", productHandler.GetProducts)
		}
	}

	// 启动服务器
	log.Println("Server starting on :8080")
	r.Run(":8080")
}
