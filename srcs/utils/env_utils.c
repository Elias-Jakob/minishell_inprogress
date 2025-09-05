void	env_value_update(char *name, char *new_name);
// 1. gets *name
// 2. create new name
//		- if that fails let everything un touched
// 3. free *name
// 4. set *name to new name
void	env_name_add(t_exec_context *exec_context, char *new_element);
// 1. alloc for envp + 1 for new element
// 2. copy envp into the new alloced envp
// 3. last element gets to be new element
// 4. free_str_arr the old envp
void	env_name_remove(t_exec_context *exec_context, char *name);
// 1. gets *name
// 2. alloc for envp - 1
// 3. copy everything from envp over to alloc if envp[i] != name
// 4. free_str_arr the old envp
