package com.example.project_one;

import org.springframework.data.repository.CrudRepository;

import com.example.project_one.Task;

// This will be AUTO IMPLEMENTED by Spring into a Bean called userRepository
// CRUD refers Create, Read, Update, Delete

public interface TaskRepository extends CrudRepository<Task, Integer> {

}