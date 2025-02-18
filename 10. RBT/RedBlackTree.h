#pragma once

#include <iostream>
#include <string>
#include "Node.h"
#include <Windows.h>

// ���� �� Ʈ�� Ŭ����
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// ��� �˻� �Լ�
	bool Find(int data, Node** outNode);

	// ��� �߰� �Լ�
	bool Insert(int data);

	// ��� ��� �Լ�
	void Print(int depth = 0, int blackCount = 0);

	void Remove(int data);

private:

	// ��� ���� �Լ�
	Node* CreateNode(int data, Color color);

	// ��� �˻� ��� �Լ�
	bool FindRecursive(Node* node, Node** outNode, int data);

	// ��� �߰� �Լ�( �� ��� ����)
	void Insert(Node* newNode);

	// Ʈ���� ��带 �߰��ϴ� ��� �Լ�
	void InsertRecursive(Node* node, Node* newNode);

	// ��� ���� �� �������� ó���ϴ� �Լ�
	void RestructureAfterInsert(Node* newNode);

	// ��� ���� �� ������ ó�� �Լ�
	void RestructureAfterRemove(Node* node);

	// ��ȸ�� �Լ�
	// node: ȸ���� ������(pivot) -> �ڼ� �������� �θ� ������
	void RotateToLeft(Node* node);

	// ��ȸ�� �Լ�
	void RotateToRight(Node* node);

	// Ʈ������ �ּڰ��� ���� ��带 �˻��ϴ� �Լ�
	Node* FindMinRecursive(Node* node);

	// Ʈ������ �ִ��� ���� ��带 �˻��ϴ� �Լ�
	Node* FindMaxRecursive(Node* node);

	// ��� ���� �Լ�
	void RemoveImpl(Node* node);

	// ���� �Լ�
	void DestroyRecursive(Node* node);

	// ��� ��� �Լ�
	void PrintRecursive(Node* node, int depth, int blackCount);

private:
	// ��Ʈ ���
	Node* root = nullptr;

	// Nill ���
	static Node* nil;
};

// �ܼ� �ؽ�Ʈ ���� ������
enum class TextColor
{
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue
};

// �ܼ� �ؽ�Ʈ ���� ���� �Լ�
void SetTextColor(TextColor color);