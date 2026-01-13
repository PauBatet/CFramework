#include<views.c>

Route routes[] = {
	{"/", home},
	{"/docs", docs},
	{"/routing", routes_view},
	{"/views", views},
	{"/models", models},
	{"/templates", templates},
	{"/docker", docker},
	{"/core-concepts", core_concepts},
};
