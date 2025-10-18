package repository

import (
	"fmt"
	"gorm.io/gorm"
	"web-demo/model"
)

type ProductRepository struct {
	db *gorm.DB
}

func NewProductRepository(db *gorm.DB) *ProductRepository {
	return &ProductRepository{db: db}
}

// 根据分片ID获取表名
func (r *ProductRepository) getTableName(shardID int8) string {
	return fmt.Sprintf("products_%d", shardID)
}

// 创建产品
func (r *ProductRepository) Create(product *model.Product) error {
	tableName := r.getTableName(product.ShardID)
	return r.db.Table(tableName).Create(product).Error
}

// 根据ID获取产品
func (r *ProductRepository) GetByID(id uint64, shardID int8) (*model.Product, error) {
	var product model.Product
	tableName := r.getTableName(shardID)
	err := r.db.Table(tableName).Where("id = ?", id).First(&product).Error
	if err != nil {
		return nil, err
	}
	return &product, nil
}

// 获取产品列表（分页）
func (r *ProductRepository) GetList(shardID int8, offset, limit int) ([]model.Product, error) {
	var products []model.Product
	tableName := r.getTableName(shardID)
	err := r.db.Table(tableName).Offset(offset).Limit(limit).Find(&products).Error
	return products, err
}

// 更新产品
func (r *ProductRepository) Update(product *model.Product) error {
	tableName := r.getTableName(product.ShardID)
	return r.db.Table(tableName).Save(product).Error
}

// 删除产品
func (r *ProductRepository) Delete(id uint64, shardID int8) error {
	tableName := r.getTableName(shardID)
	return r.db.Table(tableName).Where("id = ?", id).Delete(&model.Product{}).Error
}
