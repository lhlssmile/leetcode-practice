package app

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"log"
	"web-demo/config"
	"web-demo/handler"
	"web-demo/repository"
	"web-demo/service"
)

type App struct {
	config *config.Config
	router *gin.Engine
}

func NewApp() *App {
	return &App{}
}
func (a *App) Initialize() error {
	cfg, err := config.LoadConfig()
	if err != nil {
		return err
	}
	a.config = cfg
	db, err := config.InitDatabaseYAML(cfg.Database)

	if err != nil {
		return err
	}

	productRepo := repository.NewProductRepository(db)
	productService := service.NewProductService(productRepo)
	productHandler := handler.NewProductHandler(productService)

	a.setupRoutes(productHandler)
	return nil
}

func (a *App) setupRoutes(productHandler *handler.ProductHandler) {
	gin.SetMode(a.config.Server.Mode)
	r := gin.Default()

	api := r.Group("/api/v1")
	{
		products := api.Group("/products")

		{
			products.POST("/", productHandler.CreateProduct)
			products.GET("/:id", productHandler.GetProduct)
			products.GET("/", productHandler.GetProducts)
			products.PUT("/:id", productHandler.UpdateProduct)
			products.DELETE("/:id", productHandler.DeleteProduct)
		}
		a.router = r
	}
}
func (a *App) Run() {
	port := fmt.Sprintf(":%d", a.config.Server.Port)
	log.Printf("Server starting on %s", port)
	a.router.Run(port)
}
