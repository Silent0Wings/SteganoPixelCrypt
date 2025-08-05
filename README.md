# PixelCipher

PixelCipher is a C++ tool that encodes text into images by mapping characters to pixel colors. It provides a simple form of visual encryption, turning data into colored patterns that can be decoded back to text. Lightweight, fast, and ideal for basic steganography.

---

## Encrypted Works

PixelCipher can transform full-length literary texts or lyrics into visual patterns. Below are some examples of famous works converted into `Data.bmp` images using PixelCipher:

### Dracula by Bram Stoker

<p align="center">
  <img src="Book/Dracula/Data.bmp" alt="Dracula Encrypted Image" />
</p>

### The Adventures of Sherlock Holmes by Arthur Conan Doyle

<p align="center">
  <img src="Book/Sherlock_Holmes/Data.bmp" alt="Sherlock Holmes Encrypted Image" />
</p>

### Relativity: The Special and General Theory by Albert Einstein

<p align="center">
  <img src="Book/the_Special_and_General_Theory_by_Albert_Einstein/Data.bmp" alt="Einstein Relativity Encrypted Image" />
</p>

### Universal Declaration of Human Rights

<p align="center">
  <img src="Book/Universal_Declaration_of_Human_Rights/Data.bmp" alt="UDHR Encrypted Image" />
</p>

### The Complete Works of William Shakespeare

<p align="center">
  <img src="Book/William_Shakespeare/Data.bmp" alt="Shakespeare Encrypted Image" />
</p>

### Bohemian Rhapsody by Queen (Lyrics Only)

<p align="center">
  <img src="Song/Bohemian Rhapsody/Data.bmp" alt="Bohemian Rhapsody Encrypted Image" />
</p>

---

## Example Output

This image represents the entirety of the _Moby Dick_ book in encrypted image form:

<p align="center">
  <img src="images/Moby_Dick_Converted.png" alt="Moby Dick Image" />
</p>

---

## File Structure

Each encoded text has a corresponding `Data.bmp` (visual data) and `Key.bmp` (color-key mapping) in subfolders under `Book/` or `Song/`.
