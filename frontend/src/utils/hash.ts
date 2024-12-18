import bcrypt from 'bcryptjs';

/**
 * Hashes a password using bcrypt.
 * @param password - The plain text password to hash.
 * @returns A promise that resolves to the hashed password.
 */
export const hashPassword = async (password: string): Promise<string> => {
  const saltRounds = 10;
  return await bcrypt.hash(password, saltRounds);
};

/**
 * Compares a plain text password with a hashed password.
 * @param password - The plain text password.
 * @param hashedPassword - The hashed password.
 * @returns A promise that resolves to true if passwords match, otherwise false.
 */
export const comparePassword = async (
  password: string,
  hashedPassword: string
): Promise<boolean> => {
  return await bcrypt.compare(password, hashedPassword);
};

export interface LoginRequest {
  id: string;
  email: string;
  token: string;
  password: string;
}

export const compare_auth_token = (input:LoginRequest) => {
  return input.token === input.id+input.email
}

export const generate_auth_token = (input:LoginRequest) => {
  return input.id+input.email
}