const http = require('http');

const PORT = 8080;
const HOST = 'localhost';

// Hardcoded credentials
const VALID_USERNAME = 'ben';
const VALID_PASSWORD = 'tau';

// Create the server
const server = http.createServer((req, res) => {
  if (req.method === 'POST' && req.url === '/') {
    let body = '';

    // Collect the data
    req.on('data', chunk => {
      body += chunk.toString(); // Convert Buffer to string
    });

    // Process the data
    req.on('end', () => {
      // Parse the form data
      const parsedData = new URLSearchParams(body);
      const username = parsedData.get('username');
      const password = parsedData.get('password');

      res.setHeader('Content-Type', 'text/html');

      if (username && password) {
        // Validate credentials
        if (username === VALID_USERNAME && password === VALID_PASSWORD) {
          res.write('<h1>Login Successful</h1>');
          res.write(`<p>Welcome, ${username}!</p>`);
        } else {
          res.write('<h1>Login Failed</h1>');
          res.write('<p>Invalid username or password.</p>');
        }
      } else {
        res.write('<h1>Error</h1>');
        res.write('<p>Username and password are required.</p>');
      }

      res.end();
    });
  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('404 Not Found');
  }
});

// Start the server
server.listen(PORT, HOST, () => {
  console.log(`Server running at http://${HOST}:${PORT}/`);
});
