/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 03:28:28 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:28:29 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>
#include <deque>
#include <iostream>
#include <sys/time.h>
#include <fstream>

void printStack(std::stack<int, std::vector<int> > s, int i)
{
	i--;
	if (s.empty())
		return ;
	int x = s.top();
	s.pop();
	printStack(s, i);
	std::cout << "stack[" << i << "] = " << x << std::endl;
	i++;
	s.push(x);
}

void printStack(std::stack<int, std::deque<int> > s, int i)
{
	i--;
	if (s.empty())
		return ;
	int x = s.top();
	s.pop();
	printStack(s, i);
	std::cout << "stack[" << i << "] = " << x << std::endl;
	i++;
	s.push(x);
}

int main(void)
{
	std::cout << " ---------------------------------------------------------------------------------------------------------------------------------------------------------------- " << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                          VECTOR TESTS                                                                          |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << " ---------------------------------------------------------------------------------------------------------------------------------------------------------------- " << std::endl;
	std::cout << std::endl;
	
	std::ofstream	out_file;
	out_file.open("std_time.txt");
	struct timeval begin, end;
	long seconds = 0;
	long microseconds = 0;
	double elapsed = 0;
	
	//-------------------------------------------------------------------------------- PUSH_BACK --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- PUSH_BACK --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::vector<int> std_vector;
	std::cout << "Filling vector with 10 ints :" << std::endl;
	int i = 0;
	while (i < 10)
	{
		gettimeofday(&begin, 0);
		std_vector.push_back(i);
		gettimeofday(&end, 0);
    	seconds = end.tv_sec - begin.tv_sec;
    	microseconds = end.tv_usec - begin.tv_usec;
    	elapsed = seconds + microseconds*1e-6;
		out_file << "push_back time: " << elapsed << std::endl;
		std::cout << "vector[" << i << "] = [" << std_vector[i] << "] size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl;
		i++;
	}
	std::cout << std::endl;

	//-------------------------------------------------------------------------------- ITERATORS --------------------------------------------------------------------------------
	std::cout << "--------------------------------------------------------------------------------ITERATORS --------------------------------------------------------------------------------" << std::endl << std::endl;

	std::vector<int>::iterator std_it = std_vector.begin();
	std::cout << "Iterating over vector with iterator :" << std::endl;
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::vector<int>::reverse_iterator std_rit = std_vector.rbegin();
	std::cout << "Iterating over vector with reverse_iterator :" << std::endl;
	i = 0;
	while (std_rit != std_vector.rend())
	{
		std::cout << "vector[" << i << "] = [" << *std_rit << "]" << std::endl;
		i++;
		std_rit++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	//-------------------------------------------------------------------------------- RESIZE --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- RESIZE --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Resizing vector to 5 and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	std_vector.resize(5);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "resize time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::cout << "Resizing vector to 10 without val (= 0) and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);	
	std_vector.resize(10);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "resize time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;
	
	std::cout << "Resizing vector to 20 with val = 10 and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);	
	std_vector.resize(20, 10);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "resize fill time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;
	
	//-------------------------------------------------------------------------------- RESERVE --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- RESERVE --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Reserving 50 for vector and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	std_vector.reserve(50);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "reserve time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	//-------------------------------------------------------------------------------- ASSIGN --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- ASSIGN --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Assigning 20 val = 1 to vector and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	std_vector.assign(20, 1);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "assign fill time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::cout << "Assigning 60 val = 2 to vector and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	std_vector.assign(60, 2);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "assign fill time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::vector<int> std_vector1;
	std::cout << "Filling vector1 with 10 ints :" << std::endl;
	i = 0;
	while (i < 10)
	{
		std_vector1.push_back(i);
		std::cout << "vector1[" << i << "] = [" << std_vector1[i] << "]" << std::endl;
		i++;
	}
	std::cout << "size = " << std_vector1.size() << " capacity = " << std_vector1.capacity() << std::endl << std::endl;

	std::cout << "Assigning values between first (vector1[2]) and last (vector1[6]) iterators to vector and iterating over vector with reinitialized iterator :" << std::endl;
	std::vector<int>::iterator std_first_it = std_vector1.begin();
	std_first_it += 2;
	std::vector<int>::iterator std_last_it = std_vector1.begin();
	std_last_it += 6;
	gettimeofday(&begin, 0);
	std_vector.assign(std_first_it, std_last_it);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "assign range time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;
	
	//-------------------------------------------------------------------------------- POP_BACK --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- POP_BACK --------------------------------------------------------------------------------" << std::endl << std::endl;

	std::cout << "Resizing vector to 5 and iterating over vector with reinitialized iterator :" << std::endl;
	std_vector.resize(5);
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
	
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::cout << "Popping back on vector and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	std_vector.pop_back();
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "pop_back time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	//-------------------------------------------------------------------------------- INSERT --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- INSERT --------------------------------------------------------------------------------" << std::endl << std::endl;

	std::cout << "Inserting a single val = 66 at 3rd element on vector and iterating over vector with reinitialized iterator :" << std::endl;
	std::vector<int>::iterator std_insert_it = std_vector.begin();
	std_insert_it += 2;
	gettimeofday(&begin, 0);
	std::vector<int>::iterator std_return_it = std_vector.insert(std_insert_it, 66);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "insert time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << " value of returned iterator = " << *std_return_it << std::endl << std::endl;
	
	std::cout << "Inserting 5 val = 67 at 4th element on vector and iterating over vector with reinitialized iterator :" << std::endl;
	std_insert_it = std_vector.begin();
	std_insert_it += 3;
	gettimeofday(&begin, 0);
	std_vector.insert(std_insert_it, 5, 67);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "insert fill time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::vector<int> std_vector2;
	std::cout << "Filling vector2 with 80 ints :" << std::endl;
	i = 0;
	while (i < 80)
	{
		std_vector2.push_back(i);
		std::cout << "vector2[" << i << "] = [" << std_vector2[i] << "]" << std::endl;
		i++;
	}
	std::cout << "size = " << std_vector2.size() << " capacity = " << std_vector2.capacity() << std::endl << std::endl;

	std::cout << "Inserting values between first (vector2[2]) and last (vector2[78]) iterators to vector at 8th element and iterating over vector with reinitialized iterator :" << std::endl;
	std_first_it = std_vector2.begin();
	std_first_it += 2;
	std_last_it = std_vector2.begin();
	std_last_it += 78;
	std_insert_it = std_vector.begin();
	std_insert_it += 7;
	gettimeofday(&begin, 0);
	std_vector.insert(std_insert_it, std_first_it, std_last_it);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "insert range time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::vector<int> std_vector3;
	std::cout << "Filling vector3 with 10 ints :" << std::endl;
	i = 0;
	while (i < 10)
	{
		std_vector3.push_back(i);
		std::cout << "vector3[" << i << "] = [" << std_vector3[i] << "]" << std::endl;
		i++;
	}
	std::cout << "size = " << std_vector3.size() << " capacity = " << std_vector3.capacity() << std::endl << std::endl;

	std::cout << "Inserting 20 val = 42 at 6th element on vector3 and iterating over vector3 with reinitialized iterator :" << std::endl;
	std_insert_it = std_vector3.begin();
	std_insert_it += 5;
	gettimeofday(&begin, 0);
	std_vector3.insert(std_insert_it, 20, 42);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "insert fill time: " << elapsed << std::endl;
	std_it = std_vector3.begin();
	i = 0;
	while (std_it != std_vector3.end())
	{
		std::cout << "vector3[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector3.size() << " capacity = " << std_vector3.capacity() << std::endl << std::endl;

	//-------------------------------------------------------------------------------- CLEAR --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- CLEAR --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Clearing vector and iterating over vector with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	std_vector.clear();
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "clear time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "There is obviously absolutely nothing -_-" << std::endl;
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	//-------------------------------------------------------------------------------- ERASE --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- ERASE --------------------------------------------------------------------------------" << std::endl << std::endl;

	std::cout << "Filling vector with 10 ints :" << std::endl;
	i = 0;
	while (i < 10)
	{
		std_vector.push_back(i);
		std::cout << "vector[" << i << "] = [" << std_vector[i] << "]" << std::endl;
		i++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::cout << "Erasing 3rd element of vector and iterating over vector with reinitialized iterator :" << std::endl;
	std::vector<int>::iterator std_erase_it = std_vector.begin();
	std_erase_it += 2;
	gettimeofday(&begin, 0);
	std_return_it = std_vector.erase(std_erase_it);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "erase time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << " value of returned iterator = " << *std_return_it << std::endl << std::endl;

	std::cout << "Erasing elements in range [2, 5] of vector and iterating over vector with reinitialized iterator :" << std::endl;
	std_first_it = std_vector.begin();
	std_last_it = std_vector.begin();
	std_first_it += 2;
	std_last_it += 4;
	gettimeofday(&begin, 0);
	std_return_it = std_vector.erase(std_first_it, std_last_it);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "erase range time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << " value of returned iterator = " << *std_return_it << std::endl << std::endl;

	//-------------------------------------------------------------------------------- AT --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- AT --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "At vector[5] :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "vector[5] = " << std_vector.at(5) << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "at time: " << elapsed << std::endl;

	try
	{
		std::cout << "At vector[666] :" << std::endl;
		gettimeofday(&begin, 0);
		std::cout << "exception = " << std_vector.at(666) << std::endl << std::endl;
		gettimeofday(&end, 0);
    	seconds = end.tv_sec - begin.tv_sec;
    	microseconds = end.tv_usec - begin.tv_usec;
    	elapsed = seconds + microseconds*1e-6;
		out_file << "at time: " << elapsed << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	//-------------------------------------------------------------------------------- FRONT --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- FRONT --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Front of vector :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "front = " << std_vector.front() << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "front time: " << elapsed << std::endl;

	//-------------------------------------------------------------------------------- BACK --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- BACK --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Back of vector :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "back = " << std_vector.back() << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "back time: " << elapsed << std::endl;

	//-------------------------------------------------------------------------------- MAX_SIZE --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- MAX_SIZE --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Vector max size :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << std_vector.max_size() << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "max_size time: " << elapsed << std::endl;

	//-------------------------------------------------------------------------------- EMPTY --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- EMPTY --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Testing empty() with same vector :" << std::endl;
	bool	res;
	gettimeofday(&begin, 0);
	res = std_vector.empty();
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "empty time: " << elapsed << std::endl;
	std::cout << "bool = " << res << std::endl << std::endl;

	std::cout << "Testing empty() with new empty vector :" << std::endl;
	std::vector<int> empty_std_vector;
	gettimeofday(&begin, 0);
	res = empty_std_vector.empty();
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "empty time: " << elapsed << std::endl;
	std::cout << "bool = " << res << std::endl << std::endl;

	//-------------------------------------------------------------------------------- SWAP --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- SWAP --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Iterating over vector with reinitialized iterator :" << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::cout << "Filling vector4 with 15 ints :" << std::endl;
	std::vector<int> std_vector4;
	i = 0;
	while (i < 15)
	{
		std_vector4.push_back(i);
		std::cout << "vector4[" << i << "] = [" << std_vector4[i] << "]" << std::endl;
		i++;
	}
	std::cout << "size = " << std_vector4.size() << " capacity = " << std_vector4.capacity() << std::endl << std::endl;
	
	std::cout << "Swapping vector with vector4 and iterating over vector and vector4 with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	std_vector.swap(std_vector4);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "swap time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end()) 
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;
	
	std_it = std_vector4.begin();
	i = 0;
	while (std_it != std_vector4.end())
	{
		std::cout << "vector4[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector4.size() << " capacity = " << std_vector4.capacity() << std::endl << std::endl;

	//-------------------------------------------------------------------------------- NON-MEMBER SWAP --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- NON-MEMBER SWAP --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::cout << "Iterating over vector with reinitialized iterator :" << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end())
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;

	std::cout << "Iterating over vector4 with reinitialized iterator :" << std::endl;
	std_it = std_vector4.begin();
	i = 0;
	while (std_it != std_vector4.end())
	{
		std::cout << "vector4[" << i << "] = [" << std_vector4[i] << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector4.size() << " capacity = " << std_vector4.capacity() << std::endl << std::endl;
	
	std::cout << "Swapping vector with vector4 and iterating over vector and vector4 with reinitialized iterator :" << std::endl;
	gettimeofday(&begin, 0);
	swap(std_vector, std_vector4);
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "non-member swap time: " << elapsed << std::endl;
	std_it = std_vector.begin();
	i = 0;
	while (std_it != std_vector.end()) 
	{
		std::cout << "vector[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector.size() << " capacity = " << std_vector.capacity() << std::endl << std::endl;
	
	std_it = std_vector4.begin();
	i = 0;
	while (std_it != std_vector4.end())
	{
		std::cout << "vector4[" << i << "] = [" << *std_it << "]" << std::endl;
		i++;
		std_it++;
	}
	std::cout << "size = " << std_vector4.size() << " capacity = " << std_vector4.capacity() << std::endl << std::endl;

	//-------------------------------------------------------------------------------- RELATIONAL OPERATORS --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- RELATIONAL OPERATORS --------------------------------------------------------------------------------" << std::endl << std::endl;

	std::cout << "vector3 == vector4 :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "bool = " << (std_vector3 == std_vector4) << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "== time: " << elapsed << std::endl;

	std::cout << "vector3 != vector4 :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "bool = " << (std_vector3 != std_vector4) << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "!= time: " << elapsed << std::endl;

	std::cout << "vector3 < vector4 :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "bool = " << (std_vector3 < std_vector4) << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "<swap> time: " << elapsed << std::endl;

	std::cout << "vector3 <= vector4 :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "bool = " << (std_vector3 <= std_vector4) << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "<= time: " << elapsed << std::endl;

	std::cout << "vector3 > vector4 :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "bool = " << (std_vector3 > std_vector4) << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "> time: " << elapsed << std::endl;

	std::cout << "vector3 >= vector4 :" << std::endl;
	gettimeofday(&begin, 0);
	std::cout << "bool = " << (std_vector3 >= std_vector4) << std::endl << std::endl;
	gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << ">= time: " << elapsed << std::endl;

	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//--------------------STACK--------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	
	std::cout << " ---------------------------------------------------------------------------------------------------------------------------------------------------------------- " <<std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                          STACK TESTS                                                                           |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << " ---------------------------------------------------------------------------------------------------------------------------------------------------------------- " <<std::endl;
	std::cout << std::endl;

	//-------------------------------------------------------------------------------- PUSH --------------------------------------------------------------------------------
	std::cout << "-------------------------------------------------------------------------------- PUSH --------------------------------------------------------------------------------" << std::endl << std::endl;
	
	std::vector<int> stack_vec;
	std::stack<int, std::vector<int> > std_stack (stack_vec);
	std::cout << "Filling and printing vector stack with 10 ints using top empty push and pop :" << std::endl;
	i = 0;
	while (i < 10)
	{
		gettimeofday(&begin, 0);
		std_stack.push(i);
		gettimeofday(&end, 0);
		i++;
    	seconds = end.tv_sec - begin.tv_sec;
    	microseconds = end.tv_usec - begin.tv_usec;
    	elapsed = seconds + microseconds*1e-6;
		out_file << "vector push time: " << elapsed << std::endl;
	}
	gettimeofday(&begin, 0);
	printStack(std_stack, std_stack.size());
	gettimeofday(&end, 0);
	i++;
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "vector print time using top empty push and pop: " << elapsed << std::endl;
	std::cout << std::endl;

	std::deque<int> stack_deq;
	std::stack<int, std::deque<int> > std_stack2 (stack_deq);
	std::cout << "Filling and printing deque stack with 10 ints using top empty push and pop :" << std::endl;
	i = 0;
	while (i < 10)
	{
		gettimeofday(&begin, 0);
		std_stack2.push(i);
		gettimeofday(&end, 0);
		i++;
    	seconds = end.tv_sec - begin.tv_sec;
    	microseconds = end.tv_usec - begin.tv_usec;
    	elapsed = seconds + microseconds*1e-6;
		out_file << "deque push time: " << elapsed << std::endl;
	}
	gettimeofday(&begin, 0);
	printStack(std_stack2, std_stack2.size());
	gettimeofday(&end, 0);
	i++;
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
	out_file << "deque print time using top empty push and pop: " << elapsed << std::endl;
	std::cout << std::endl;

	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//--------------------MAP----------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------
	
	std::cout << " ---------------------------------------------------------------------------------------------------------------------------------------------------------------- " <<std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                          MAP TESTS                                                                             |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << "|                                                                                                                                                                |" << std::endl;
	std::cout << " ---------------------------------------------------------------------------------------------------------------------------------------------------------------- " <<std::endl;
	std::cout << std::endl;
	
	{

		std::cout << "==== Iterators & Insert ====" << std::endl;
		
		std::map<char, std::string>				std_map;
		std::map<char, std::string>::iterator	std_it;

		gettimeofday(&begin, 0);
		std_map.insert(std::make_pair('1', "salut"));
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Insert Time: " << elapsed << std::endl;

		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_it = std_map.begin();

		std::cout << "map.begin():" << std::endl;
		std::cout << "	" << std_it->second << std::endl;

		std_it++;

		std::cout << "it++:" << std::endl;
		std::cout<< "	IT: " << std_it->second << std::endl;

		std_it = std_map.end();

		std_it = std_map.insert(std_it, std::make_pair('3', "ciao"));

		std::cout << "new insert:" << std::endl;
		std::cout<< "	IT: " << std_it->second << std::endl;

		std_it = std_map.begin();

		std::cout << "while it != end():" << std::endl;
		while (std_it != std_map.end())
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.begin();

		std::map<char, std::string>::iterator	std_it2;

		std_it2 = std_map.end();

		std::cout << "while it != it2:" << std::endl;
		while (std_it != std_it2)
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.begin();

		std::cout << "while it2 != it:" << std::endl;
		while (std_it != std_it2)
		{
			std_it2--;
			std::cout << "	IT = " << std_it2->second << std::endl;
		}
		
		std_it = std_map.begin();
		std_it2 = std_map.end();

		bool res = (std_it == std_it2);
		bool res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;

		std_it2 = std_map.begin();

		res = (std_it == std_it2);
		res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;

		std_it = std_map.begin();
		std_it2 = std_map.end();

		std_map.insert(std_it, std_it2);
		std::cout << "	" << std_it->second << std::endl;
	}

	{
		std::cout << "==== Reverse Iterators & Insert ====" << std::endl;
		std::map<char, std::string>				std_map;
		std::map<char, std::string>::reverse_iterator	std_it;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_it = std_map.rbegin();

		std::cout << "map.rbegin():" << std::endl;
		std::cout << "	" << std_it->second << std::endl;

		std_it++;

		std::cout << "it++:" << std::endl;
		std::cout<< "	IT: " << std_it->second << std::endl;

		std_it = std_map.rend();

		std_it = std_map.rbegin();

		std::cout << "while it != rend():" << std::endl;
		while (std_it != std_map.rend())
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.rbegin();

		std::map<char, std::string>::reverse_iterator	std_it2;

		std_it2 = std_map.rend();

		std::cout << "while it != it2:" << std::endl;
		while (std_it != std_it2)
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.rbegin();

		std::cout << "while it2 != it:" << std::endl;
		while (std_it != std_it2)
		{
			std_it2--;
			std::cout << "	IT = " << std_it2->second << std::endl;
		}

		std_it = std_map.rbegin();
		std_it2 = std_map.rend();

		bool res = (std_it == std_it2);
		bool res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;

		std_it2 = std_map.rbegin();

		res = (std_it == std_it2);
		res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;
	}

	{
		std::cout << "==== Const Iterators & Insert ====" << std::endl;
		std::map<char, std::string>				std_map;
		std::map<char, std::string>::const_iterator	std_it;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_it = std_map.begin();

		std::cout << "map.begin():" << std::endl;
		std::cout << "	" << std_it->second << std::endl;

		std_it++;

		std::cout << "it++:" << std::endl;
		std::cout<< "	IT: " << std_it->second << std::endl;

		std_it = std_map.begin();

		std::cout << "while it != end():" << std::endl;
		while (std_it != std_map.end())
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.begin();

		std::map<char, std::string>::const_iterator	std_it2;

		std_it2 = std_map.end();

		std::cout << "while it != it2:" << std::endl;
		while (std_it != std_it2)
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.begin();

		std::cout << "while it2 != it:" << std::endl;
		while (std_it != std_it2)
		{
			std_it2--;
			std::cout << "	IT = " << std_it2->second << std::endl;
		}

		std_it = std_map.begin();
		std_it2 = std_map.end();

		bool res = (std_it == std_it2);
		bool res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;

		std_it2 = std_map.begin();

		res = (std_it == std_it2);
		res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;
	}

	{
		std::cout << "==== Const Reverse Iterators & Insert ====" << std::endl;
		std::map<char, std::string>							std_map;
		std::map<char, std::string>::const_reverse_iterator	std_it;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_it = std_map.rbegin();

		std::cout << "map.rbegin():" << std::endl;
		std::cout << "	" << std_it->second << std::endl;

		std_it++;

		std::cout << "it++:" << std::endl;
		std::cout<< "	IT: " << std_it->second << std::endl;

		std_it = std_map.rend();

		std_it = std_map.rbegin();

		std::cout << "while it != end():" << std::endl;
		while (std_it != std_map.rend())
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.rbegin();

		std::map<char, std::string>::const_reverse_iterator	std_it2;

		std_it2 = std_map.rend();

		std::cout << "while it != it2:" << std::endl;
		while (std_it != std_it2)
		{
			std::cout << "	IT = " << std_it->second << std::endl;
			std_it++;
		}

		std_it = std_map.rbegin();

		std::cout << "while it2 != it:" << std::endl;
		while (std_it != std_it2)
		{
			std_it2--;
			std::cout << "	IT = " << std_it2->second << std::endl;
		}

		std_it = std_map.rbegin();
		std_it2 = std_map.rend();

		bool res = (std_it == std_it2);
		bool res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;

		std_it2 = std_map.rbegin();

		res = (std_it == std_it2);
		res1 = (std_it != std_it2);

		std::cout << "	==: " << res << std::endl;
		std::cout << "	!=: " << res1 << std::endl;
	}

	{
		std::cout << "==== Operator[] ====" << std::endl;
		std::map<char, std::string>				std_map;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std::cout << "	map['2']: " << std_map['2'] << std::endl;
		std::cout << "	map['4']: " << std_map['4'] << std::endl;
		
		std_map['4'] = "gazou";

		std::cout << "	map['4']: " << std_map['4'] << std::endl;
	}

	{
		std::cout << "==== Operator= ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2 = std_map;
		
		std::cout << "	map['0']: " << std_map['0'] << std::endl;
		std::cout << "	map2['0']: " << std_map2['0'] << std::endl;
	}

	{
		std::cout << "==== Empty ====" << std::endl;

		std::map<char, std::string>				std_map;

		gettimeofday(&begin, 0);
		bool res = std_map.empty();
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Empty: " << elapsed << std::endl;
		std::cout << "	" << res << std::endl;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		res = std_map.empty();
		std::cout << "	" << res << std::endl;
	}

	{
		std::cout << "==== Size ====" << std::endl;

		std::map<char, std::string>				std_map;

		gettimeofday(&begin, 0);
		size_t res = std_map.size();
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Size: " << elapsed << std::endl;
		std::cout << "	" << res << std::endl;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		res = std_map.size();
		std::cout << "	" << res << std::endl;
	}

	{
		std::cout << "==== Max Size ====" << std::endl;

		std::map<char, std::string>				std_map;

		gettimeofday(&begin, 0);
		size_t res = std_map.max_size();
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Max Size: " << elapsed << std::endl;
		std::cout << "	" << res << std::endl;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		res = std_map.max_size();
		std::cout << "	" << res << std::endl;
	}

	{
		std::cout << "==== Clear ====" << std::endl;

		std::map<char, std::string>				std_map;

		size_t res = std_map.size();
		std::cout << "	" << res << std::endl;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		res = std_map.size();
		std::cout << "	" << res << std::endl;

		gettimeofday(&begin, 0);
		std_map.clear();
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Clear: " << elapsed << std::endl;

		res = std_map.size();
		std::cout << "	" << res << std::endl;
	}

	{
		std::cout << "==== Erase ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>::iterator	std_it;
		std::map<char, std::string>::iterator	std_it2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std::cout << "	map['2']: " <<  std_map['2'] << std::endl;

		size_t res = std_map.size();
		std::cout << "	size: " << res << std::endl;

		gettimeofday(&begin, 0);
		std_map.erase('2');
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Erase: " << elapsed << std::endl;

		res = std_map.size();
		std::cout << "	size: " << res << std::endl;
		std::cout << "	map['2']: " <<  std_map['2'] << std::endl;

		std_it = std_map.begin();
		std::cout << "	IT: " << std_it->second << std::endl;
		std_it2 = std_it;
		std_it2++;
		std::cout << "	IT: " << std_it2->second << std::endl;

		res = std_map.size();
		std::cout << "	size: " << res << std::endl;
		std::cout << "	map['0']: " << std_map['0'] << std::endl;
		std::cout << "	map['2']: " << std_map['2'] << std::endl;

		std_it = std_map.insert(std_it, std::make_pair('3', "coucou"));
		std::cout << "	IT: " << std_it->second << std::endl;

		std::cout << "	map['3']: " << std_map['3'] << std::endl;
		std_map.erase(std_it);
		std::cout << "	map['3']: " << std_map['3'] << std::endl;
		res = std_map.size();
		std::cout << "	size: " << res << std::endl;
	}

	{
		std::cout << "==== Swap ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;
		std::map<char, std::string>::iterator	std_it;
		std::map<char, std::string>::iterator	std_it2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "SALUT"));
		std_map2.insert(std::make_pair('2', "COUCOU"));
		std_map2.insert(std::make_pair('0', "HELLO"));

		std_it = std_map.begin();
		while (std_it != std_map.end())
		{
			std::cout << "	map['" << std_it->first << "']: " << std_it->second << std::endl;
			std_it++;
		}

		std_it2 = std_map2.begin();
		while (std_it2 != std_map2.end())
		{
			std::cout << "	map2['" << std_it2->first << "']: " << std_it2->second << std::endl;
			std_it2++;
		}

		gettimeofday(&begin, 0);
		std_map.swap(std_map2);
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Swap: " << elapsed << std::endl;

		std_it = std_map.begin();
		while (std_it != std_map.end())
		{
			std::cout << "	map['" << std_it->first << "']: " << std_it->second << std::endl;
			std_it++;
		}

		std_it2 = std_map2.begin();
		while (std_it2 != std_map2.end())
		{
			std::cout << "	map2['" << std_it2->first << "']: " << std_it2->second << std::endl;
			std_it2++;
		}
	}

	{
		std::cout << "==== Count ====" << std::endl;

		std::map<char, std::string>				std_map;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		gettimeofday(&begin, 0);
		size_t res = std_map.count('4');
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Count: " << elapsed << std::endl;
		std::cout << "	map count: " << res << std::endl;

		res = std_map.count('2');
		std::cout << "	map count: " << res << std::endl;
	}

	{
		std::cout << "==== Find ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>::iterator	std_it;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));


		gettimeofday(&begin, 0);
		std_it = std_map.find('0');
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Find: " << elapsed << std::endl;
		std::cout << "	IT: " << std_it->second << std::endl;
	}

	{
		std::cout << "==== Equal Range ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::pair<std::map<char, std::string>::iterator, std::map<char, std::string>::iterator>			it;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		gettimeofday(&begin, 0);
		it = std_map.equal_range('0');
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Equal Range: " << elapsed << std::endl;
    	std::cout << "	The lower bound is " << it.first->first << ":" << it.first->second << std::endl;
	
    	std::cout << "	The upper bound is " << it.second->first << ":" << it.second->second << std::endl;

		it = std_map.equal_range('-');
    	std::cout << "	The lower bound is " << it.first->first << ":" << it.first->second << std::endl;
	
    	std::cout << "	The upper bound is " << it.second->first << ":" << it.second->second << std::endl;
	}

	{
		std::cout << "==== Lower Bound ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>::iterator	std_it;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		gettimeofday(&begin, 0);
		std_it = std_map.lower_bound('0');
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Lower Bound: " << elapsed << std::endl;
		std::cout << "	The lower bound is " << std_it->first << ":" << std_it->second << std::endl;

		std_it = std_map.lower_bound('-');
		std::cout << "	The lower bound is " << std_it->first << ":" << std_it->second << std::endl;
	}

	{
		std::cout << "==== Upper Bound ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>::iterator	std_it;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		gettimeofday(&begin, 0);
		std_it = std_map.upper_bound('0');
		gettimeofday(&end, 0);
    	long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;
		out_file << "Upper Bound: " << elapsed << std::endl;
		std::cout << "	The upper bound is " << std_it->first << ":" << std_it->second << std::endl;

		std_it = std_map.upper_bound('-');
		std::cout << "	The upper bound is " << std_it->first << ":" << std_it->second << std::endl;
	}

	{
		std::cout << "==== == Comparison ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));

		bool res = (std_map == std_map2);
		std::cout << "	==: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));
		std_map2.insert(std::make_pair('3', "hello"));

		res = (std_map == std_map2);
		std::cout << "	==: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "helloo"));

		res = (std_map == std_map2);
		std::cout << "	==: " << res << std::endl;
	}

	{
		std::cout << "==== != Comparison ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));

		bool res = (std_map != std_map2);
		std::cout << "	!=: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));
		std_map2.insert(std::make_pair('3', "hello"));

		res = (std_map != std_map2);
		std::cout << "	!=: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "helloo"));

		res = (std_map != std_map2);
		std::cout << "	!=: " << res << std::endl;
	}

	{
		std::cout << "==== < Comparison ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));

		bool res = (std_map < std_map2);
		std::cout << "	<: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));
		std_map2.insert(std::make_pair('3', "hello"));

		res = (std_map < std_map2);
		std::cout << "	<: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "helloo"));

		res = (std_map < std_map2);
		std::cout << "	<: " << res << std::endl;
	}

	{
		std::cout << "==== <= Comparison ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));

		bool res = (std_map <= std_map2);
		std::cout << "	<=: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));
		std_map2.insert(std::make_pair('3', "hello"));

		res = (std_map <= std_map2);
		std::cout << "	<=: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "helloo"));

		res = (std_map <= std_map2);
		std::cout << "	<=: " << res << std::endl;
	}

	{
		std::cout << "==== > Comparison ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));

		bool res = (std_map > std_map2);
		std::cout << "	>: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));
		std_map2.insert(std::make_pair('3', "hello"));

		res = (std_map > std_map2);
		std::cout << "	>: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "helloo"));

		res = (std_map > std_map2);
		std::cout << "	>: " << res << std::endl;
	}

	{
		std::cout << "==== >= Comparison ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));

		bool res = (std_map >= std_map2);
		std::cout << "	>=: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "hello"));
		std_map2.insert(std::make_pair('3', "hello"));

		res = (std_map >= std_map2);
		std::cout << "	>=: " << res << std::endl;

		std_map2.clear();

		std_map2.insert(std::make_pair('1', "salut"));
		std_map2.insert(std::make_pair('2', "coucou"));
		std_map2.insert(std::make_pair('0', "helloo"));

		res = (std_map >= std_map2);
		std::cout << "	>=: " << res << std::endl;
	}

	{
		std::cout << "==== 2 Maps Swap ====" << std::endl;

		std::map<char, std::string>				std_map;
		std::map<char, std::string>				std_map2;
		std::map<char, std::string>::iterator	std_it;
		std::map<char, std::string>::iterator	std_it2;

		std_map.insert(std::make_pair('1', "salut"));
		std_map.insert(std::make_pair('2', "coucou"));
		std_map.insert(std::make_pair('0', "hello"));

		std_map2.insert(std::make_pair('1', "SALUT"));
		std_map2.insert(std::make_pair('2', "COUCOU"));
		std_map2.insert(std::make_pair('0', "HELLO"));

		std_it = std_map.begin();
		while (std_it != std_map.end())
		{
			std::cout << "	map['" << std_it->first << "']: " << std_it->second << std::endl;
			std_it++;
		}

		std_it2 = std_map2.begin();
		while (std_it2 != std_map2.end())
		{
			std::cout << "	map2['" << std_it2->first << "']: " << std_it2->second << std::endl;
			std_it2++;
		}

		std::swap(std_map, std_map2);

		std_it = std_map.begin();
		while (std_it != std_map.end())
		{
			std::cout << "	map['" << std_it->first << "']: " << std_it->second << std::endl;
			std_it++;
		}

		std_it2 = std_map2.begin();
		while (std_it2 != std_map2.end())
		{
			std::cout << "	map2['" << std_it2->first << "']: " << std_it2->second << std::endl;
			std_it2++;
		}
	}
	return (0);
}