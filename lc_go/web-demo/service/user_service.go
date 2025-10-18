package service

import (
	"web-demo/model"
	"web-demo/repository"
)

type ProductService struct {
	productRepo *repository.ProductRepository
}

func NewProductService(productRepo *repository.ProductRepository) *ProductService {
	return &ProductService{
		productRepo: productRepo,
	}
}

// 创建产品
func (s *ProductService) CreateProduct(product *model.Product) error {
	// 这里可以添加业务逻辑，比如数据验证
	return s.productRepo.Create(product)
}

// 获取产品
func (s *ProductService) GetProduct(id uint64, shardID int8) (*model.Product, error) {
	return s.productRepo.GetByID(id, shardID)
}

// 获取产品列表
func (s *ProductService) GetProducts(shardID int8, page, pageSize int) ([]model.Product, error) {
	offset := (page - 1) * pageSize
	return s.productRepo.GetList(shardID, offset, pageSize)
}

// 更新产品
func (s *ProductService) UpdateProduct(product *model.Product) error {
	// 这里可以添加业务逻辑
	return s.productRepo.Update(product)
}

// 删除产品
func (s *ProductService) DeleteProduct(id uint64, shardID int8) error {
	return s.productRepo.Delete(id, shardID)
}
