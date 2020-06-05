specialization_id(const specialization_id& rhs) = delete; // (1)
  
specialization_id(specialization_id&& rhs) = delete; // (2)

specialization_id &operator=(const specialization_id& rhs) = delete; // (3)

specialization_id &operator=(specialization_id&& rhs) = delete; // (4)