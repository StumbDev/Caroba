export const SITE = {
  title: 'Caroba Documentation',
  description: 'Documentation for the Caroba programming language',
  defaultLanguage: 'en',
  twitter: '@caroba_lang',
  github: 'caroba/caroba',
  version: 'v0.0.3'
};

export const OPEN_GRAPH = {
  image: {
    src: 'caroba-banner.jpg',
    alt: 'Caroba - A C-compatible language with @ syntax'
  }
};

export const SIDEBAR = {
  en: [
    { text: 'Introduction', header: true },
    { text: 'Getting Started', link: 'getting-started' },
    { text: 'Installation', link: 'installation' },
    
    { text: 'Core Concepts', header: true },
    { text: 'Basic Syntax', link: 'basic-syntax' },
    { text: 'Types', link: 'types' },
    { text: 'Functions', link: 'functions' },
    { text: 'Memory Management', link: 'memory-management' },
    
    { text: 'Advanced Topics', header: true },
    { text: 'C Interop', link: 'c-interop' },
    { text: 'Standard Library', link: 'stdlib' },
    { text: 'Best Practices', link: 'best-practices' }
  ]
}; 