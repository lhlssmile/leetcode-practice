package model

import (
	_ "gorm.io/gorm"
	"time"
)

type Product struct {
	ID            uint64    `json:"id" gorm:"primaryKey;autoIncrement"`
	ParentAsin    string    `json:"parent_asin" gorm:"uniqueIndex;not null"`
	Title         string    `json:"title"`
	MainCategory  string    `json:"main_category"`
	Price         float64   `json:"price"`
	AverageRating float64   `json:"average_rating"`
	RatingNumber  int       `json:"rating_number"`
	Store         string    `json:"store"`
	Inventory     int       `json:"inventory" gorm:"not null"`
	ShardID       int8      `json:"shard_id" gorm:"not null"`
	CreatedAt     time.Time `json:"created_at"`
	UpdatedAt     time.Time `json:"updated_at"`
}
