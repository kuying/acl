#include "stdafx.h"
#include <list>
#include <vector>
#include <map>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "struct.h"  // 由 gson 工具根据 struct.stub 转换而成
#include "gson.h"    // 由 gson 工具根据 struct.stub 生成

// 序列化过程
static void serialize(void)
{
	user u;

	u.name = "zsxxsz";
	u.age = 11;
	u.male = true;

	u.province_name = "山东省";
	u.position = "山东省";

	u.shcool = "山东工业大学";
	u.class_name = "热处理专业";

	acl::json json;

	// 将 user 对象转换为 json 对象
	acl::json_node& node = acl::gson(json, u);

	printf("serialize:\r\n");
	printf("json: %s\r\n", node.to_string().c_str());
	printf("\r\n");
}

// 反序列化过程
static void deserialize(void)
{
	const char *s = "{\"shcool\": \"山东工业大学\", \"class_name\": \"热处理专业\", \"province_name\": \"山东省\", \"position\": \"山东省\", \"name\": \"zsxxsz\", \"age\": 11, \"male\": true}";
	printf("deserialize:\r\n");

	acl::json json;
	json.update(s);
	user u;

	// 将 json 对象转换为 user 对象
	std::pair<bool, std::string> ret = acl::gson(json.get_root(), u);

	// 如果转换失败，则打印转换失败原因
	if (ret.first == false)
		printf("error: %s\r\n", ret.second.c_str());
	else
	{
		printf("name: %s, age: %d, male: %s\r\n",
			u.name.c_str(), u.age, u.male ? "yes" : "no");
		printf("province_name: %s, position: %s\r\n",
			u.province_name.c_str(), u.position.c_str());
		printf("shcool: %s, class_name: %s\r\n",
			u.shcool.c_str(), u.class_name.c_str());
	}
}

static void test1(void)
{
	union
	{
		struct user_male*   m;
		struct user_female* f;
		struct people*      p;
	} obj;

	struct user_male* m = new struct user_male;
	(*m).favorite = "pingpang";
	(*m).height = 170;
	(*m).name = "zsxxsz";
	(*m).age = 11;
	(*m).male = true;

	(*m).province_name = "山东省";
	(*m).position = "山东省";

	(*m).shcool = "山东工业大学";
	(*m).class_name = "热处理专业";

	obj.m = m;
	acl::json json;

	// 将 user 对象转换为 json 对象
	acl::json_node& node = acl::gson(json, obj.m);

	printf("serialize:\r\n");
	printf("json: %s\r\n", node.to_string().c_str());
	printf("\r\n");

	delete obj.p;
}

static void test2(void)
{
	const char *s = "{\"shcool\": \"山东工业大学\", \"class_name\": \"热处理专业\", \"province_name\": \"山东省\", \"position\": \"山东省\", \"name\": \"zsxxsz\", \"age\": 11, \"male\": true, \"favorite\": \"pingpang\", \"height\": 170}";
	printf("deserialize:\r\n");

	acl::json json;
	json.update(s);
	user_male u;

	// 将 json 对象转换为 user 对象
	std::pair<bool, std::string> ret = acl::gson(json.get_root(), u);

	// 如果转换失败，则打印转换失败原因
	if (ret.first == false)
		printf("error: %s\r\n", ret.second.c_str());
	else
	{
		printf("name: %s, age: %d, male: %s, favorite: %s, height: %d\r\n",
			u.name.c_str(), u.age, u.male ? "yes" : "no",
			u.get_favorite(), u.get_height());
		printf("province_name: %s, position: %s\r\n",
			u.province_name.c_str(), u.position.c_str());
		printf("shcool: %s, class_name: %s\r\n",
			u.shcool.c_str(), u.class_name.c_str());
	}
}

int main(void)
{
	printf("------------------------serialize----------------------\r\n");
	serialize();

	printf("------------------------deserialize--------------------\r\n");
	deserialize();

	printf("------------------------test1--------------------------\r\n");
	test1();

	printf("------------------------test2--------------------------\r\n");
	test2();

	return 0;
}
