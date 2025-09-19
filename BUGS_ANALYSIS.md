# ANALYSE DES BUGS - MINISHELL

## **Problèmes identifiés dans tasks.txt :**

### **2. Bug de redirection (echo "Hello world" > out) - ERREUR DE CONDITION**
- **Localisation :** `srcs/execution/redirect.c:62`
- **Problème :** Condition incorrecte dans `setup_redirections`
```c
// INCORRECT (ligne 62):
if (redirs->fds[1] != STDOUT_FILENO && redirs->fds[1] != STDIN_FILENO)

// DEVRAIT ÊTRE:
if (redirs->fds[1] != STDOUT_FILENO && redirs->fds[1] != -1)
```

### **3. Export/Unset dans pipeline - FONCTION MANQUANTE**
- **Localisation :** `srcs/parser/management_command.c:61`
- **Problème :** Appel à `is_token_builtin()` qui n'existe pas
- **Erreur de compilation :** Cette fonction est référencée mais pas définie
- **Impact :** Les builtins ne sont pas détectés correctement dans les pipelines

**Solution nécessaire :**
```c
// À ajouter dans parser/utils.c ou management_command.c
int is_token_builtin(t_token *token)
{
    if (!token || !token->value)
        return (EXIT_FAILURE);
    if (!ft_strncmp(token->value, "echo", 5) ||
        !ft_strncmp(token->value, "cd", 3) ||
        !ft_strncmp(token->value, "pwd", 4) ||
        !ft_strncmp(token->value, "export", 7) ||
        !ft_strncmp(token->value, "unset", 6) ||
        !ft_strncmp(token->value, "env", 4) ||
        !ft_strncmp(token->value, "exit", 5))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}
```

### **4. Heredoc expansion ($() et $xx) - NON IMPLÉMENTÉE**
- **Localisation :** `srcs/parser/heredoc.c:63-64`
- **Problème :** Le heredoc n'effectue pas l'expansion des variables/commandes
- **Détail :** Les lignes sont écrites directement sans traitement des `$`

**Solutions nécessaires :**
- Expansion des variables `$VAR` dans le heredoc
- Command substitution `$()` dans le heredoc
- Gestion de `$?` dans le heredoc

**Code à modifier dans `create_heredoc_file` :**
```c
// Avant d'écrire la ligne, faire l'expansion
char *expanded_line = expand_variables_in_heredoc(line, env);
write(fd, expanded_line, ft_strlen(expanded_line));
write(fd, "\n", 1);
free(expanded_line);
```

### **5. Heredoc dans redirections - IMPLÉMENTATION INCOMPLÈTE**
- **Localisation :** `srcs/execution/redirect.c:19-20, 49-50`
- **Problème :** Les cas `RD_HEREDOC` retournent sans traitement
- **Détail :** Pas d'ouverture du fichier temporaire créé par heredoc

**Solution nécessaire :**
```c
// Dans set_in_fd, remplacer le return par:
else if (redirs->in_type == RD_HEREDOC && redirs->heredoc_content)
{
    redirs->fds[0] = open(redirs->heredoc_content, O_RDONLY);
    if (redirs->fds[0] == -1)
        fatal_error(exec_context, "heredoc file open failed");
}
```

## **Actions recommandées par priorité :**

### **CRITIQUE (bloque la compilation/exécution) :**
1. **Ajouter la fonction `is_token_builtin` manquante** - `management_command.c:61`
2. **Corriger le bug de redirection** - `redirect.c:62`

### **IMPORTANT (fonctionnalités manquantes) :**
3. **Implémenter l'expansion `$?` dans le lexer** - `scan_token.c:113-118`
4. **Compléter l'expansion dans heredoc** - `heredoc.c:63-64`

### **MOYEN (améliorations) :**
5. **Finaliser la gestion heredoc dans les redirections** - `redirect.c:19-20, 49-50`

## **Tests de validation :**

```bash
# Test $?
echo "test" | grep "nothing"; echo $?  # Devrait afficher 1

# Test redirection
echo "Hello world" > out; cat out  # Devrait créer le fichier

# Test pipeline builtin
export hye=hye | unset hye  # Ne devrait pas dire "command not found"

# Test heredoc expansion
cat << EOF
Hello $USER
$(date)
Exit status: $?
EOF
```

## **Fichiers à modifier :**

1. `srcs/lexer/scan_token.c` - Ajouter gestion $?
2. `srcs/execution/redirect.c` - Corriger condition ligne 62 et heredoc
3. `srcs/parser/management_command.c` ou `utils.c` - Ajouter is_token_builtin
4. `srcs/parser/heredoc.c` - Ajouter expansion variables/commandes
5. `includes/parser.h` - Déclarer is_token_builtin

---

*Analyse effectuée le 2025-09-19*
