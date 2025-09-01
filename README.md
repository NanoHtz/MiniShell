<!-- ===================== BANNER ===================== -->
<p align="center">
  <img src="https://raw.githubusercontent.com/NanoHtz/Assets/main/minishell/banner.svg" alt="Philosophers banner">
</p>

<p align="center"><i>🖥️ Minishell (42 Cursus) — Intérprete de shell en C con lexer/parser, pipes, redirecciones, expansión de variables, heredoc, señales y built-ins (comportamiento tipo bash).</i></p>

---

## Índice
- [Resumen](#resumen)
- [¿Para qué?](#para-que)
- [Explicación](#explicacion)
- [Compilación](#compilacion)
- [Uso](#uso)
- [Salida esperada y pruebas](#salida)

---

<a id="resumen"></a>
## ✅ Resumen del proyecto

**Minishell** es un shell interactivo escrito en C. Implementa **tokenización y parseo**, **pipes y redirecciones** (`|`, `>`, `>>`, `<`, `<<`), **expansión de variables** (incl. `$?`), **comillas simples/dobles**, **heredoc** y **built-ins** (`cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit`). Maneja **señales** como `Ctrl+C` y reproduce el comportamiento esencial de **bash** (códigos de salida y mensajes de error incluidos).

---

<a id="para-que"></a>
## 🧩 ¿Para qué?

**¿Qué se aprende?**
- **Parseo**: lexer/tokenizer, gramática mínima y construcción de comandos/pipelines.
- **Procesos y E/S**: `fork`, `execve`, `dup2`, `pipe`, `close`.
- **Redirecciones**: `>`, `>>`, `<`, `<<` (heredoc) y gestión de ficheros.
- **Expansión** de variables, reglas de comillas y `$?`.
- **Built-ins** y diferencias padre/hijo (entorno del shell).
- **Señales**: `SIGINT`/`SIGQUIT` en modo interactivo y heredoc.
- **Errores y códigos de salida** compatibles con bash.
- **Memoria**: diseño sin fugas, cierre ordenado de FDs y limpieza final.

---

<a id="explicacion"></a>
<details>
  <summary><h3>📝 Explicación</h3></summary>

<b>🧭 Flujo general</b><br>
1) Leer línea → 2) Tokenizar/parsear → 3) Expandir variables → 4) Preparar redirecciones/pipes → 5) Ejecutar (built-ins o <i>execve</i>) → 6) Esperar hijos → 7) Mostrar prompt de nuevo.
<br><br>

<b>🧾 Lexer & Parser</b><br>
• Se separa en <b>tokens</b> (palabras, <code>|</code>, <code>&lt;</code>, <code>&gt;</code>, <code>&gt;&gt;</code>, <code>&lt;&lt;</code>).<br>
• <b>Comillas</b>: <code>' '</code> desactiva toda expansión; <code>" "</code> mantiene expansión de <code>$VAR</code> y respeta espacios internos.<br>
• Se construye una estructura por <b>comando</b> con su argv, redirecciones y, si procede, conexiones de <b>pipe</b>.
<br><br>

<b>💲 Expansión</b><br>
• <code>$VAR</code> y <code>$?</code> (último status).<br>
• Sin expansión entre <code>' '</code>; con expansión entre <code>" "</code>.<br>
• Expansión antes de ejecutar y antes de abrir redirecciones (con reglas especiales en heredoc).
<br><br>

<b>🔁 Pipes y redirecciones</b><br>
• <code>|</code> conecta la <b>salida</b> de un comando con la <b>entrada</b> del siguiente.<br>
• <code>&gt;</code>, <code>&gt;&gt;</code>: redirigen STDOUT (truncate / append).<br>
• <code>&lt;</code>: redirige STDIN desde fichero.<br>
• <code>&lt;&lt;</code> (heredoc): lee hasta el <b>delimitador</b>. Si el delimitador está entre <code>' '</code>, no se expanden <code>$</code>.
<br><br>

<b>⚙️ Built-ins</b><br>
• Implementados: <code>echo</code>, <code>cd</code>, <code>pwd</code>, <code>env</code>, <code>export</code>, <code>unset</code>, <code>exit</code>.<br>
• <b>cd/export/unset/exit</b> deben ejecutarse en el proceso <b>padre</b> cuando no hay pipe, para que afecten al entorno del shell.
<br><br>

<b>🧷 Señales</b><br>
• Interactivo: <b>Ctrl+C</b> (SIGINT) cancela la línea actual y muestra prompt en nueva línea; <b>Ctrl+\</b> (SIGQUIT) se ignora.<br>
• En procesos hijos, las señales se comportan como en bash (p.ej. <code>cat</code> abortado con SIGINT → status 130).
<br><br>

<b>📦 Heredoc</b><br>
• Captura entrada hasta el delimitador; si el delimitador va <b>entre comillas</b>, no hay expansión.<br>
• <b>Ctrl+C</b> durante heredoc cancela el heredoc y vuelve al prompt (sin cerrar el shell).
<br><br>

<b>📤 Códigos de salida (compatibles)</b><br>
• Comando no encontrado → <b>127</b>.<br>
• Permiso denegado / no ejecutable → <b>126</b>.<br>
• Señal SIGINT en un proceso → <b>130</b>; SIGQUIT → <b>131</b>.<br>
• Error de <b>sintaxis</b> (p.ej., <code>|</code> inesperado) → <b>258</b>.<br>
• <code>exit</code> usa su argumento numérico (módulo 256) o el último status.
<br><br>

<b>🧊 Casos borde</b><br>
• Múltiples espacios/quotes anidadas: el parser debe conservar el contenido exacto tras expansión.<br>
• Redirecciones encadenadas y pipes largos: cerrar todos los FDs no usados.<br>
• Heredoc + señales: cancelar limpio FDs temporales.
<br><br>

</details>

---

<a id="compilacion"></a>
## 🛠️ Compilación

⬇️ Descarga
```bash
git clone <https://github.com/NanoHtz/MiniShell>.git
```
